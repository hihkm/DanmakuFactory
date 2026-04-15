import 'package:freezed_annotation/freezed_annotation.dart';

import '../../../../../repository/settings_repository.dart';

part 'preset_state.freezed.dart';

@freezed
abstract class PresetState with _$PresetState {
  const PresetState._();

  const factory PresetState({
    //文本大小
    @Default(SettingsRepository.DEFAULT_TEXT_SIZE) int textSize,
    //文本阴影:0-4 整数
    @Default(SettingsRepository.DEFAULT_TEXT_SHADOW) int textShadow,
    //文本透明度:0-255 整数
    @Default(SettingsRepository.DEFAULT_TEXT_OPACITY) int textOpacity,
    //文本描边:0-4 整数
    @Default(SettingsRepository.DEFAULT_TEXT_OUTLINE) int textOutline,
    //是否粗体
    @Default(SettingsRepository.DEFAULT_IS_BOLD) bool isBold,
    //滚动弹幕通过时间
    @Default(SettingsRepository.DEFAULT_DANMAKU_SCROLL_TIME)
    double danmakuScrollTime,
    //固定弹幕停留时间
    @Default(SettingsRepository.DEFAULT_DANMAKU_FIXED_TIME)
    double danmakuFixedTime,
    //弹幕密度:-1 不重叠,0 无限制,其他 表示限定条数
    @Default(SettingsRepository.DEFAULT_DANMAKU_DENSITY) int danmakuDensity,
    //弹幕屏蔽模式列表:要屏蔽的弹幕类型名称，用-连接:L2R, R2L, TOP, BOTTOM, SPECIAL, COLOR, REPEAT
    @Default(SettingsRepository.DEFAULT_DANMAKU_BLOCK_MODE_LIST)
    List<String> danmakuBlockModeList,
    //滚动弹幕显示区域:0.0-1.0 浮点数
    @Default(SettingsRepository.DEFAULT_DANMAKU_SCROLL_AREA)
    double danmakuScrollArea,
    //全部弹幕显示区域:0.0-1.0 浮点数
    @Default(SettingsRepository.DEFAULT_DANMAKU_ALL_AREA) double danmakuAllArea,
    //分辨率宽 度
    @Default(SettingsRepository.DEFAULT_RESOLUTION_WIDTH) int resolutionWidth,
    // 分辨率高度
    @Default(SettingsRepository.DEFAULT_RESOLUTION_HEIGHT) int resolutionHeight,
    // 错误信息
    String? errMsg,
  }) = _PresetState;
}

//屏蔽弹幕模式枚举
enum DanmakuBlockMode {
  //L2R, R2L, TOP, BOTTOM, SPECIAL, COLOR, REPEAT
  L2R("左右滚动", "L2R"),
  R2L("右左滚动", "R2L"),
  TOP("顶部固定", "TOP"),
  BOTTOM("底部固定", "BOTTOM"),
  SPECIAL("特殊", "SPECIAL"),
  COLOR("非白色", "COLOR"),
  REPEAT("内容重复", "REPEAT");

  final String title;
  final String value;

  const DanmakuBlockMode(this.title, this.value);
}
