import 'dart:async';
import 'dart:io';
import 'package:flutter/foundation.dart';

/// 是否是harmonyOS
bool get isOhos => Platform.operatingSystem.toLowerCase() == 'ohos';

/// 是否是移动设备
bool get isMobile => Platform.isAndroid || Platform.isIOS || isOhos;

/// 是否是桌面端
bool get isDesktop =>
    Platform.isWindows || Platform.isMacOS || Platform.isLinux;

/// 跨平台方法，可选回调，返回值支持泛型
T runPlatform<T>({
  T Function()? onAndroid,
  T Function()? onIOS,
  T Function()? onWindows,
  T Function()? onMacOS,
  T Function()? onLinux,
  T Function()? onOhos,
  T Function()? onWeb,
  required T Function() orElse, // 通用方法，必须提供
}) {
  if (kIsWeb) {
    return (onWeb ?? orElse)();
  } else if (Platform.isAndroid) {
    return (onAndroid ?? orElse)();
  } else if (Platform.isIOS) {
    return (onIOS ?? orElse)();
  } else if (Platform.isWindows) {
    return (onWindows ?? orElse)();
  } else if (Platform.isMacOS) {
    return (onMacOS ?? orElse)();
  } else if (Platform.isLinux) {
    return (onLinux ?? orElse)();
  } else if (isOhos) {
    return (onOhos ?? orElse)();
  } else {
    return orElse();
  }
}

T runPlatformGroup<T>({
  T Function()? onMobile,
  T Function()? onDesktop,
  T Function()? onWeb,
  required T Function() orElse, // 必须提供通用方法
}) {
  if (kIsWeb) {
    return (onWeb ?? orElse)();
  } else if (isMobile) {
    return (onMobile ?? orElse)();
  } else if (isDesktop) {
    return (onDesktop ?? orElse)();
  } else {
    return orElse();
  }
}

Future<T> runPlatformAsync<T>({
  FutureOr<T> Function()? onAndroid,
  FutureOr<T> Function()? onIOS,
  FutureOr<T> Function()? onWindows,
  FutureOr<T> Function()? onMacOS,
  FutureOr<T> Function()? onLinux,
  FutureOr<T> Function()? onOhos,
  FutureOr<T> Function()? onWeb,
  required FutureOr<T> Function() orElse, // 必须提供
}) async {
  FutureOr<T> Function()? func;

  if (kIsWeb) {
    func = onWeb ?? orElse;
  } else if (Platform.isAndroid) {
    func = onAndroid ?? orElse;
  } else if (Platform.isIOS) {
    func = onIOS ?? orElse;
  } else if (Platform.isWindows) {
    func = onWindows ?? orElse;
  } else if (Platform.isMacOS) {
    func = onMacOS ?? orElse;
  } else if (Platform.isLinux) {
    func = onLinux ?? orElse;
  } else if (isOhos) {
    func = onOhos ?? orElse;
  } else {
    func = orElse;
  }

  // 统一转成 Future
  return await Future.sync(func);
}

Future<T> runPlatformGroupAsync<T>({
  FutureOr<T> Function()? onMobile,
  FutureOr<T> Function()? onDesktop,
  FutureOr<T> Function()? onWeb,
  required FutureOr<T> Function() orElse, // 必须提供
}) async {
  FutureOr<T> Function()? func;

  if (kIsWeb) {
    func = onWeb ?? orElse;
  } else if (isMobile) {
    func = onMobile ?? orElse;
  } else if (isDesktop) {
    func = onDesktop ?? orElse;
  } else {
    func = orElse;
  }

  // 统一转成 Future
  return await Future.sync(func);
}
