import 'dart:io';

import 'package:danmakufactory_flutter/repository/app_repository.dart';
import 'package:danmakufactory_flutter/utils/app_util.dart';
import 'package:danmakufactory_flutter/utils/platform_util.dart';
import 'package:danmakufactory_flutter/utils/toast_util.dart';
import 'package:riverpod_annotation/riverpod_annotation.dart';
import 'package:url_launcher/url_launcher.dart';

import '../../../../../utils/file_util.dart';
import '../../home/model/home_state.dart';
import '../model/file_state.dart';
import 'package:path/path.dart' as p;

part 'file_provider.g.dart';

@riverpod
class FileNotifier extends _$FileNotifier {
  @override
  FutureOr<FileState> build() async {
    final String dirPath = await AppRepository.getDanmakuOutputDirPath();
    final Directory outputDir = Directory(dirPath);
    final List<OutputFileItemBean> outputFiles = await getOutputFileItems(
      outputDir,
    );
    return FileState(outputDir: outputDir, outputFileItems: outputFiles);
  }

  //刷新列表
  Future<void> refreshList() async {
    final current = state.requireValue;
    final outputDir = current.outputDir;
    if (outputDir == null) {
      return;
    }
    final outputFiles = await getOutputFileItems(outputDir);
    state = AsyncValue.data(current.copyWith(outputFileItems: outputFiles));
    //ToastUtil.success("刷新成功");
  }

  //打开输出文件夹
  Future<void> openOutputDir() async {
    final current = state.requireValue;
    final outputDir = current.outputDir;
    if (outputDir == null) {
      return;
    }

    ToastUtil.warning("正在打开输出文件夹,请稍后", milliseconds: 1000);

    final targetPath = outputDir.path;

    final openResult = await FileUtil.openFolder(targetPath);
    if (!openResult) {
      ToastUtil.error("不支持打开输出文件夹,请手动打开路径:${targetPath}");
    }
  }

  //分享文件
  Future<void> shareFiles() async {
    final files = getCheckedFiles();
    if (files.isEmpty) {
      ToastUtil.warning("请选择要分享的文件");
      return;
    }
    final result = await FileUtil.shareFiles(files);
    if (!result) {
      ToastUtil.error("分享失败,请手动打开文件");
    }
  }

  //删除文件
  Future<void> deleteFiles() async {
    final files = getCheckedFiles();
    if (files.isEmpty) {
      ToastUtil.warning("请选择要删除的文件");
      return;
    }
    final result = await FileUtil.deleteFiles(files);
    if (!result) {
      ToastUtil.error("删除失败,请手动删除文件");
    }

    refreshList();
  }

  //获取checked的文件
  List<File> getCheckedFiles() {
    final current = state.requireValue;
    final files = current.outputFileItems
        .where((fileItem) => fileItem.checked)
        .map((fileItem) => fileItem.file)
        .toList();
    return files;
  }

  // 切换全选状态
  void toggleAllCheckStatus() {
    final status = isAllChecked();
    changeAllCheckStatus(!status);
  }

  //改变全选状态
  void changeAllCheckStatus(bool status) {
    final current = state.requireValue;

    state = AsyncValue.data(
      current.copyWith(
        outputFileItems: current.outputFileItems.map((fileItem) {
          return OutputFileItemBean(fileItem.file, status);
        }).toList(),
      ),
    );
  }

  //判断是否为全选
  bool isAllChecked() {
    final current = state.value;
    if (current == null) {
      return false;
    }
    return current.outputFileItems.every((fileItem) => fileItem.checked);
  }

  //选中item
  void checkOutputFileItem(OutputFileItemBean selectItem) {
    final current = state.requireValue;

    // 创建新的文件列表，切换选中项的状态
    final newOutputItems = current.outputFileItems.map((fileItem) {
      if (fileItem == selectItem) {
        // 找到匹配的 item,切换其 checked 状态
        return OutputFileItemBean(selectItem.file, !selectItem.checked);
      }
      return fileItem;
    }).toList();

    final newState = current.copyWith(outputFileItems: newOutputItems);

    state = AsyncValue.data(newState);
  }

  Future<List<OutputFileItemBean>> getOutputFileItems(Directory dir) async {
    final List<File> danmakuFiles = await getDanmakuFiles(dir);
    final List<OutputFileItemBean> outputFiles = danmakuFiles
        .map((item) => OutputFileItemBean(item, false))
        .toList();
    return outputFiles;
  }

  //获取指定文件夹下面所有的文件,后缀为DanmakuFormat枚举
  Future<List<File>> getDanmakuFiles(Directory dir) async {
    if (!dir.existsSync()) {
      dir.createSync(recursive: true);
      return [];
    }

    // 获取所有支持的弹幕格式后缀
    final supportedExtensions = DanmakuFormat.values
        .map((format) => format.value)
        .toList();

    // 获取目录下所有文件
    final entities = dir.listSync().whereType<File>().toList();

    // 筛选出支持的弹幕格式文件
    final danmakuFiles = entities.where((file) {
      final extension = p.extension(file.path).toLowerCase().substring(1);
      return supportedExtensions.contains(extension);
    }).toList();

    return danmakuFiles;
  }
}
