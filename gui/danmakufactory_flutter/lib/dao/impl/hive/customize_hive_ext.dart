import 'dart:io';

import 'package:flutter/foundation.dart';
import 'package:flutter/widgets.dart';
import 'package:hive_ce_flutter/adapters.dart';
import 'package:hive_ce_flutter/src/wrapper/path_provider.dart';
import 'package:hive_ce_flutter/src/wrapper/path.dart' as path_helper;
import 'package:path/path.dart' as p;
import '../../../utils/platform_util.dart';

/// Flutter extensions for Hive.
extension CustomizeHiveExt on HiveInterface {
  /// Initializes Hive with the path from [getApplicationDocumentsDirectory].
  ///
  /// You can provide a [subDir] where the boxes should be stored.
  ///
  /// Also registers the flutter type adapters.
  Future<void> initHive([
    String? subDir,
    HiveStorageBackendPreference backendPreference =
        HiveStorageBackendPreference.native,
    int? colorAdapterTypeId,
    int? timeOfDayAdapterTypeId,
  ]) async {
    WidgetsFlutterBinding.ensureInitialized();

    String? path;
    if (!kIsWeb) {
      final appDir = await getCustomSavePath();
      path = path_helper.join(appDir.path, subDir);
    }

    init(
      path,
      backendPreference: backendPreference,
    );

    final colorAdapter = ColorAdapter(typeId: colorAdapterTypeId);
    if (!isAdapterRegistered(colorAdapter.typeId)) {
      registerAdapter(colorAdapter);
    }

    final timeOfDayAdapter = TimeOfDayAdapter(typeId: timeOfDayAdapterTypeId);
    if (!isAdapterRegistered(timeOfDayAdapter.typeId)) {
      registerAdapter(timeOfDayAdapter);
    }
  }

  
  //获取自定义存储路径
  Future<Directory> getCustomSavePath() async {
    final dirName = 'storage';

    final path = await runPlatformAsync<String>(
      onWindows: () {
        final exePath = Platform.resolvedExecutable;
        final dir = p.dirname(exePath);
        return p.join(dir, dirName);
      },
      onLinux: () {
        final exePath = Platform.resolvedExecutable;
        final dir = p.dirname(exePath);
        return p.join(dir, dirName);
      },
      orElse: () async {
        final appDocDir = await getApplicationDocumentsDirectory();
        return p.join(appDocDir.path, dirName);
      },
    );

    //判断是否存在
    final dir = Directory(path);
    if (!dir.existsSync()) {
      dir.createSync(recursive: true);
    }

    return dir;
  }

}