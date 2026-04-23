import 'dart:io';

import 'package:danmakufactory_flutter/repository/app_repository.dart';
import 'package:danmakufactory_flutter/ui/screen/main/home/model/home_state.dart';
import 'package:danmakufactory_flutter/utils/platform_util.dart';
import 'package:danmakufactory_flutter/utils/toast_util.dart';
import 'package:file_picker/file_picker.dart';
import 'package:path_provider/path_provider.dart';
import 'package:path/path.dart' as p;
import 'package:riverpod_annotation/riverpod_annotation.dart';

import '../../../../../repository/settings_repository.dart';
import '../../../../../service/danmaku_service.dart';

part 'home_provider.g.dart';

@riverpod
class HomeNotifier extends _$HomeNotifier {
  @override
  HomeState build() {
    final outputFormatVal = SettingsRepository.loadOutputDanmakuFormat();
    final outputFormat = _getDanmakuFormatByValue(outputFormatVal);

    return HomeState(outputDanmakuFormat: outputFormat);
  }

  late final _danmakuService = DanmakuService();

  //转换弹幕
  void convertDanmaku() async {
    if (state.inputFiles.isEmpty) {
      ToastUtil.warning('请先选择输入文件');
      return;
    }
    //获取输出格式
    final outputFormatExt = state.outputDanmakuFormat.value;

    //获取输出文件夹
    final outputDirPath = await AppRepository.getDanmakuOutputDirPath();
    final outputDir = Directory(outputDirPath);
    if (!outputDir.existsSync()) {
      outputDir.createSync(recursive: true);
    }

    _danmakuService.convertDanmakuList(
      state.inputFiles,
      outputDirPath,
      outputFormatExt,
    );
  }

  //选择输入文件
  void pickInputFiles() async {
    final FilePickerResult? result = await FilePicker.platform.pickFiles(
      withData: Platform.isMacOS,
      allowMultiple: true,
      type: FileType.custom,
      allowedExtensions: DanmakuFormat.values
          .map((item) => item.value)
          .toList(),
    );
    if (result == null) {
      return;
    }

    final paths = await runPlatformAsync(
      onMacOS: () async {
        final tempDir = await getTemporaryDirectory();

        final List<String> targetPathList = [];

        for (final file in result.files) {
          final timestamp = DateTime.now().millisecondsSinceEpoch;
          final newPath = p.join(tempDir.path, timestamp.toString(), file.name);
          final bytes = file.bytes;
          if (bytes == null) {
            continue;
          }
          final newFile = File(newPath);
          await newFile.parent.create(recursive: true);
          await newFile.writeAsBytes(bytes);
          targetPathList.add(newPath);
        }

        return targetPathList;
      },
      orElse: () {
        return result.paths.nonNulls.toList();
      },
    );

    state = state.copyWith(inputFiles: paths);
  }

  ///改变输出格式
  void changeOutputDanmakuFormat(String formatVal) {
    final format = _getDanmakuFormatByValue(formatVal);
    state = state.copyWith(outputDanmakuFormat: format);
    // 持久化
    SettingsRepository.saveOutputDanmakuFormat(formatVal);
  }

  DanmakuFormat _getDanmakuFormatByValue(String value) {
    return DanmakuFormat.values.firstWhere(
      (element) => element.value == value,
      orElse: () => DanmakuFormat.ass,
    );
  }
}
