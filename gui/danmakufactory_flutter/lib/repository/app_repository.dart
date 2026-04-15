import 'dart:io';

import 'package:danmakufactory_flutter/repository/settings_repository.dart';
import 'package:path_provider/path_provider.dart';
import '../utils/platform_util.dart';
import 'package:path/path.dart' as p;

class AppRepository {
  AppRepository._();

  static Future<void> init() async {
    // 初始化设置仓库
    await SettingsRepository.init();
  }

  static const String DANMAKU_OUTPUT_DIR_NAME = "danmakufactoryOutput";
  static String? _cacheDanmakuOutputDirPath;

  // 获取弹幕输出目录
  static Future<String> getDanmakuOutputDirPath() async {
    if (_cacheDanmakuOutputDirPath != null) {
      return _cacheDanmakuOutputDirPath!;
    }
    _cacheDanmakuOutputDirPath = await runPlatformAsync<String>(
      onWindows: () {
        final exePath = Platform.resolvedExecutable;
        final dir = p.dirname(exePath);
        return p.join(dir, DANMAKU_OUTPUT_DIR_NAME);
      },
      onLinux: () {
        final exePath = Platform.resolvedExecutable;
        final dir = p.dirname(exePath);
        return p.join(dir, DANMAKU_OUTPUT_DIR_NAME);
      },
      orElse: () async {
        final appDocDir = await getApplicationDocumentsDirectory();
        return p.join(appDocDir.path, DANMAKU_OUTPUT_DIR_NAME);
      },
    );
    return _cacheDanmakuOutputDirPath!;
  }
}
