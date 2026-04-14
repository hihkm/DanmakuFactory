
import 'dart:async';
import 'dart:ffi' as ffi;
import 'dart:io';
import 'dart:isolate';
import 'package:ffi/ffi.dart' ;

import 'danmakufactory_bindings_generated.dart';

String testHi() => _bindings.testHi().cast<Utf8>().toDartString();

int runCmd(String cmd) => _bindings.runCmd(cmd.toNativeUtf8().cast<ffi.Char>());

Future<int> runCmdAsync(String cmd) async {
  final SendPort helperIsolateSendPort = await _helperIsolateSendPort;
  final int requestId = _nextRunCmdRequestId++;
  final _RunCmdRequest request = _RunCmdRequest(requestId, cmd);
  final Completer<int> completer = Completer<int>();
  _runCmdRequests[requestId] = completer;
  helperIsolateSendPort.send(request);
  return completer.future;
}

int sum(int a, int b) => _bindings.sum(a, b);

Future<int> sumAsync(int a, int b) async {
  final SendPort helperIsolateSendPort = await _helperIsolateSendPort;
  final int requestId = _nextSumRequestId++;
  final _SumRequest request = _SumRequest(requestId, a, b);
  final Completer<int> completer = Completer<int>();
  _sumRequests[requestId] = completer;
  helperIsolateSendPort.send(request);
  return completer.future;
}

const String _libName = 'danmakufactory';

/// The dynamic library in which the symbols for [DanmakufactoryBindings] can be found.
final ffi.DynamicLibrary _dylib = () {
  if (Platform.isMacOS || Platform.isIOS) {
    return ffi.DynamicLibrary.open('$_libName.framework/$_libName');
  }
  if (Platform.isAndroid || Platform.isLinux || Platform.operatingSystem == 'ohos') {
    return ffi.DynamicLibrary.open('lib$_libName.so');
  }
  if (Platform.isWindows) {
    return ffi.DynamicLibrary.open('$_libName.dll');
  }
  throw UnsupportedError('Unknown platform: ${Platform.operatingSystem}');
}();

/// The bindings to the native functions in [_dylib].
final DanmakufactoryBindings _bindings = DanmakufactoryBindings(_dylib);


class _SumRequest {
  final int id;
  final int a;
  final int b;

  const _SumRequest(this.id, this.a, this.b);
}

class _SumResponse {
  final int id;
  final int result;

  const _SumResponse(this.id, this.result);
}

/// Counter to identify [_SumRequest]s and [_SumResponse]s.
int _nextSumRequestId = 0;

/// Mapping from [_SumRequest] `id`s to the completers corresponding to the correct future of the pending request.
final Map<int, Completer<int>> _sumRequests = <int, Completer<int>>{};

class _RunCmdRequest {
  final int id;
  final String cmd;

  const _RunCmdRequest(this.id, this.cmd);
}

class _RunCmdResponse {
  final int id;
  final int statusCode;

  const _RunCmdResponse(this.id, this.statusCode);
}

int _nextRunCmdRequestId = 0;

final Map<int, Completer<int>> _runCmdRequests = <int, Completer<int>>{};

/// The SendPort belonging to the helper isolate.
Future<SendPort> _helperIsolateSendPort = () async {
  // The helper isolate is going to send us back a SendPort, which we want to
  // wait for.
  final Completer<SendPort> completer = Completer<SendPort>();

  // Receive port on the main isolate to receive messages from the helper.
  // We receive two types of messages:
  // 1. A port to send messages on.
  // 2. Responses to requests we sent.
  final ReceivePort receivePort = ReceivePort()
    ..listen((dynamic data) {
      if (data is SendPort) {
        // The helper isolate sent us the port on which we can sent it requests.
        completer.complete(data);
        return;
      }
      if (data is _SumResponse) {
        // The helper isolate sent us a response to a request we sent.
        final Completer<int> completer = _sumRequests[data.id]!;
        _sumRequests.remove(data.id);
        completer.complete(data.result);
        return;
      }

      if (data is _RunCmdResponse) {
        // The helper isolate sent us a response to a runCmd request.
        final Completer<int> completer = _runCmdRequests[data.id]!;
        _runCmdRequests.remove(data.id);
        completer.complete(data.statusCode);
        return;
      }

      throw UnsupportedError('Unsupported message type: ${data.runtimeType}');
    });

  // Start the helper isolate.
  await Isolate.spawn((SendPort sendPort) async {
    final ReceivePort helperReceivePort = ReceivePort()
      ..listen((dynamic data) {
        // On the helper isolate listen to requests and respond to them.
        if (data is _SumRequest) {
          final int result = _bindings.sum_long_running(data.a, data.b);
          final _SumResponse response = _SumResponse(data.id, result);
          sendPort.send(response);
          return;
        }

        if (data is _RunCmdRequest) {
          final int statusCode = _bindings.runCmd(data.cmd.toNativeUtf8().cast<ffi.Char>());
          final _RunCmdResponse response = _RunCmdResponse(data.id, statusCode);
          sendPort.send(response);
          return;
        }

        throw UnsupportedError('Unsupported message type: ${data.runtimeType}');
      });

    // Send the port to the main isolate on which we can receive requests.
    sendPort.send(helperReceivePort.sendPort);
  }, receivePort.sendPort);

  // Wait until the helper isolate has sent us back the SendPort on which we
  // can start sending requests.
  return completer.future;
}();
