

import 'dart:io';

import 'package:freezed_annotation/freezed_annotation.dart';

part 'file_state.freezed.dart';

@freezed
abstract class FileState with _$FileState {
  const FileState._();

  const factory FileState({
    @Default([]) List<OutputFileItemBean> outputFileItems,
    Directory? outputDir,
    String? errMsg,
  }) = _FileState;
}

class OutputFileItemBean {
  final File file;
  final bool checked;

  OutputFileItemBean(this.file, this.checked);
}