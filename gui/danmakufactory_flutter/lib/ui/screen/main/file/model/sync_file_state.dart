import 'dart:io';

import 'package:freezed_annotation/freezed_annotation.dart';

part 'sync_file_state.freezed.dart';

@freezed
abstract class SyncFileState with _$SyncFileState {
  const SyncFileState._();

  const factory SyncFileState({
    @Default(false) bool isManageModel,
    String? errMsg,
  }) = _SyncFileState;
}