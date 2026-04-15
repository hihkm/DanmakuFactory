import 'dart:io';

import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import 'repository/app_repository.dart';
import 'log/provider_logger.dart';
import 'service/cmd_service.dart';
import 'ui/screen/app/app_screen.dart';

void main(List<String> args) async {
  if (CmdService.isCmdMode(args)) {
    await _handleCommand(args);
    return;
  }
  _runUi();
}

// 运行UI
Future<void> _runUi() async {
  await _init();

  final List<ProviderObserver> providerObservers = [];
  if (kDebugMode) {
    providerObservers.add(ProviderLogger());
  }

  runApp(ProviderScope(observers: providerObservers, child: const AppScreen()));
}

// 初始化
_init() async {
  WidgetsFlutterBinding.ensureInitialized();
  await AppRepository.init();
}

// 处理命令行
Future<void> _handleCommand(List<String> rawArgs) async {
  //拷贝一份
  final args = List<String>.from(rawArgs);

  await CmdService.runCmd(args);

  if (stdout.hasTerminal) {
    //退出提示
    print("Press Enter to exit...\n");
  }

  // 结束进程
  exit(0);
}
