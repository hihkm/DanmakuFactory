import 'package:danmakufactory_flutter/utils/toast_util.dart';
import 'package:riverpod_annotation/riverpod_annotation.dart';

import '../../../../../repository/settings_repository.dart';
import '../../home/model/home_state.dart';
import '../model/preset_state.dart';

part 'preset_provider.g.dart';

@riverpod
class PresetNotifier extends _$PresetNotifier {
  @override
  PresetState build() {
    final textSize = SettingsRepository.loadTextSize();
    final textShadow = SettingsRepository.loadTextShadow();
    final textOpacity = SettingsRepository.loadTextOpacity();
    final textOutline = SettingsRepository.loadTextOutline();
    final isBold = SettingsRepository.loadIsBold();
    final danmakuScrollTime = SettingsRepository.loadDanmakuScrollTime();
    final danmakuFixedTime = SettingsRepository.loadDanmakuFixedTime();
    final danmakuDensity = SettingsRepository.loadDanmakuDensity();
    final List<String> danmakuBlockModeList =
        SettingsRepository.loadDanmakuBlockModeList();
    final danmakuScrollArea = SettingsRepository.loadDanmakuScrollArea();
    final danmakuAllArea = SettingsRepository.loadDanmakuAllArea();
    final resolutionWidth = SettingsRepository.loadResolutionWidth();
    final resolutionHeight = SettingsRepository.loadResolutionHeight();

    return PresetState(
      textSize: textSize,
      textShadow: textShadow,
      textOpacity: textOpacity,
      textOutline: textOutline,
      isBold: isBold,
      danmakuScrollTime: danmakuScrollTime,
      danmakuFixedTime: danmakuFixedTime,
      danmakuDensity: danmakuDensity,
      danmakuBlockModeList: danmakuBlockModeList,
      danmakuScrollArea: danmakuScrollArea,
      danmakuAllArea: danmakuAllArea,
      resolutionWidth: resolutionWidth,
      resolutionHeight: resolutionHeight,
    );
  }

  void changeTextSize(int value) {
    state = state.copyWith(textSize: value);
    SettingsRepository.saveTextSize(value);
  }

  void changeTextShadow(int value) {
    state = state.copyWith(textShadow: value);
    SettingsRepository.saveTextShadow(value);
  }

  void changeTextOpacity(int value) {
    state = state.copyWith(textOpacity: value);
    SettingsRepository.saveTextOpacity(value);
  }

  void changeTextOutline(int value) {
    state = state.copyWith(textOutline: value);
    SettingsRepository.saveTextOutline(value);
  }

  void changeIsBold(bool value) {
    state = state.copyWith(isBold: value);
    SettingsRepository.saveIsBold(value);
  }

  void changeDanmakuScrollTime(double value) {
    state = state.copyWith(danmakuScrollTime: value);
    SettingsRepository.saveDanmakuScrollTime(value);
  }

  void changeDanmakuFixedTime(double value) {
    state = state.copyWith(danmakuFixedTime: value);
    SettingsRepository.saveDanmakuFixedTime(value);
  }

  void changeDanmakuDensity(int value) {
    state = state.copyWith(danmakuDensity: value);
    SettingsRepository.saveDanmakuDensity(value);
  }

  //显示弹幕密度说明
  void showDanmakuDensityTip() {
    ToastUtil.showAlways("-1:不重叠   0:无限制\n其他:表示限定条数");
  }

  void checkDanmakuBlockMode(DanmakuBlockMode type, bool value) {
    final saveList = List<String>.from(state.danmakuBlockModeList);

    final exist = saveList.contains(type.value);
    if (exist) {
      saveList.remove(type.value);
    } else {
      saveList.add(type.value);
    }
    state = state.copyWith(danmakuBlockModeList: saveList);
    SettingsRepository.saveDanmakuBlockModeList(saveList);
  }


  bool isDanmakuBlockMode(DanmakuBlockMode type) {
    return state.danmakuBlockModeList.contains(type.value);
  }

  void changeDanmakuScrollArea(double value) {
    state = state.copyWith(danmakuScrollArea: value);
    SettingsRepository.saveDanmakuScrollArea(value);
  }

  void changeDanmakuAllArea(double value) {
    state = state.copyWith(danmakuAllArea: value);
    SettingsRepository.saveDanmakuAllArea(value);
  }

  void changeResolutionWidth(int value) {
    state = state.copyWith(resolutionWidth: value);
    SettingsRepository.saveResolutionWidth(value);
  }

  void changeResolutionHeight(int value) {
    state = state.copyWith(resolutionHeight: value);
    SettingsRepository.saveResolutionHeight(value);
  }

  void resetToDefault() {
    state = const PresetState();
    SettingsRepository.saveTextSize(SettingsRepository.DEFAULT_TEXT_SIZE);
    SettingsRepository.saveTextShadow(SettingsRepository.DEFAULT_TEXT_SHADOW);
    SettingsRepository.saveTextOpacity(SettingsRepository.DEFAULT_TEXT_OPACITY);
    SettingsRepository.saveTextOutline(SettingsRepository.DEFAULT_TEXT_OUTLINE);
    SettingsRepository.saveIsBold(SettingsRepository.DEFAULT_IS_BOLD);
    SettingsRepository.saveDanmakuScrollTime(
      SettingsRepository.DEFAULT_DANMAKU_SCROLL_TIME,
    );
    SettingsRepository.saveDanmakuFixedTime(
      SettingsRepository.DEFAULT_DANMAKU_FIXED_TIME,
    );
    SettingsRepository.saveDanmakuDensity(
      SettingsRepository.DEFAULT_DANMAKU_DENSITY,
    );
    SettingsRepository.saveDanmakuBlockModeList(
      SettingsRepository.DEFAULT_DANMAKU_BLOCK_MODE_LIST,
    );
    SettingsRepository.saveDanmakuScrollArea(
      SettingsRepository.DEFAULT_DANMAKU_SCROLL_AREA,
    );
    SettingsRepository.saveDanmakuAllArea(
      SettingsRepository.DEFAULT_DANMAKU_ALL_AREA,
    );
    SettingsRepository.saveResolutionWidth(
      SettingsRepository.DEFAULT_RESOLUTION_WIDTH,
    );
    SettingsRepository.saveResolutionHeight(
      SettingsRepository.DEFAULT_RESOLUTION_HEIGHT,
    );
  }
}
