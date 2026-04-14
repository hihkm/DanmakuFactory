
import 'dart:io';

import 'package:danmakufactory_flutter/repository/app_repository.dart';
import 'package:danmakufactory_flutter/ui/screen/main/file/model/sync_file_state.dart';
import 'package:riverpod_annotation/riverpod_annotation.dart';

import '../../home/model/home_state.dart';
import '../model/file_state.dart';
import 'package:path/path.dart' as p;

part 'sync_file_provider.g.dart';

@riverpod
class SyncFileNotifier extends _$SyncFileNotifier {
  @override
  SyncFileState build() {
    return SyncFileState();
  }

  //切换管理模式
  bool toggleManageModel() {
    final bool after = !state.isManageModel;
    state = state.copyWith(isManageModel: after);
    return after;
  }
}