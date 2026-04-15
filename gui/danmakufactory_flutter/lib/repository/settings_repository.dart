import '../dao/impl/hive/hive_storage.dart';
import '../dao/local_storage.dart';
import '../ui/screen/main/home/model/home_state.dart';

class SettingsRepository {
  SettingsRepository._();

  static const String STORAGE_NAME = "app_settings";
  static final LocalStorage _localStorage = HiveStorage(STORAGE_NAME);

  static Future<void> init() async {
    await _localStorage.init();
    await _localStorage.open();
  }

  static final String _KEY_OUTPUT_DANMAKU_FORMAT = "KEY_OUTPUT_DANMAKU_FORMAT";

  // 设置弹幕输出格式
  static void saveOutputDanmakuFormat(String formatVal) {
    _localStorage.setValue(_KEY_OUTPUT_DANMAKU_FORMAT, formatVal);
  }

  static String loadOutputDanmakuFormat({String? defaultVal}) {
    return _localStorage.getValue(
      _KEY_OUTPUT_DANMAKU_FORMAT,
      defaultValue: defaultVal ?? DanmakuFormat.ass.value,
    );
  }

  // ==================== 默认值常量 ====================
  static const int DEFAULT_TEXT_SIZE = 38;
  static const int DEFAULT_TEXT_SHADOW = 1;
  static const int DEFAULT_TEXT_OPACITY = 180;
  static const int DEFAULT_TEXT_OUTLINE = 0;
  static const bool DEFAULT_IS_BOLD = false;
  static const double DEFAULT_DANMAKU_SCROLL_TIME = 12.0;
  static const double DEFAULT_DANMAKU_FIXED_TIME = 5.0;
  static const int DEFAULT_DANMAKU_DENSITY = 0;
  static const List<String> DEFAULT_DANMAKU_BLOCK_MODE_LIST = [];
  static const double DEFAULT_DANMAKU_SCROLL_AREA = 1.0;
  static const double DEFAULT_DANMAKU_ALL_AREA = 1.0;
  static const int DEFAULT_RESOLUTION_WIDTH = 1920;
  static const int DEFAULT_RESOLUTION_HEIGHT = 1080;


  // ==================== 文本大小 ====================
  static final String _KEY_TEXT_SIZE = "KEY_TEXT_SIZE";

  static void saveTextSize(int size) {
    _localStorage.setValue(_KEY_TEXT_SIZE, size);
  }

  static int loadTextSize({int? defaultVal}) {
    return _localStorage.getValue(
      _KEY_TEXT_SIZE,
      defaultValue: defaultVal ?? DEFAULT_TEXT_SIZE,
    );
  }

  // ==================== 文本阴影 ====================
  static final String _KEY_TEXT_SHADOW = "KEY_TEXT_SHADOW";

  static void saveTextShadow(int shadow) {
    _localStorage.setValue(_KEY_TEXT_SHADOW, shadow);
  }

  static int loadTextShadow({int? defaultVal}) {
    return _localStorage.getValue(
      _KEY_TEXT_SHADOW,
      defaultValue: defaultVal ?? DEFAULT_TEXT_SHADOW,
    );
  }

  // ==================== 文本透明度 ====================
  static final String _KEY_TEXT_OPACITY = "KEY_TEXT_OPACITY";

  static void saveTextOpacity(int opacity) {
    _localStorage.setValue(_KEY_TEXT_OPACITY, opacity);
  }

  static int loadTextOpacity({int? defaultVal}) {
    return _localStorage.getValue(
      _KEY_TEXT_OPACITY,
      defaultValue: defaultVal ?? DEFAULT_TEXT_OPACITY,
    );
  }

  // ==================== 文本描边 ====================
  static final String _KEY_TEXT_OUTLINE = "KEY_TEXT_OUTLINE";

  static void saveTextOutline(int outline) {
    _localStorage.setValue(_KEY_TEXT_OUTLINE, outline);
  }

  static int loadTextOutline({int? defaultVal}) {
    return _localStorage.getValue(
      _KEY_TEXT_OUTLINE,
      defaultValue: defaultVal ?? DEFAULT_TEXT_OUTLINE,
    );
  }

  // ==================== 是否粗体 ====================
  static final String _KEY_IS_BOLD = "KEY_IS_BOLD";

  static void saveIsBold(bool isBold) {
    _localStorage.setValue(_KEY_IS_BOLD, isBold);
  }

  static bool loadIsBold({bool? defaultVal}) {
    return _localStorage.getValue(
      _KEY_IS_BOLD,
      defaultValue: defaultVal ?? DEFAULT_IS_BOLD,
    );
  }

  // ==================== 滚动弹幕通过时间 ====================
  static final String _KEY_DANMAKU_SCROLL_TIME = "KEY_DANMAKU_SCROLL_TIME";

  static void saveDanmakuScrollTime(double time) {
    _localStorage.setValue(_KEY_DANMAKU_SCROLL_TIME, time);
  }

  static double loadDanmakuScrollTime({double? defaultVal}) {
    return _localStorage.getValue(
      _KEY_DANMAKU_SCROLL_TIME,
      defaultValue: defaultVal ?? DEFAULT_DANMAKU_SCROLL_TIME,
    );
  }

  // ==================== 固定弹幕停留时间 ====================
  static final String _KEY_DANMAKU_FIXED_TIME = "KEY_DANMAKU_FIXED_TIME";

  static void saveDanmakuFixedTime(double time) {
    _localStorage.setValue(_KEY_DANMAKU_FIXED_TIME, time);
  }

  static double loadDanmakuFixedTime({double? defaultVal}) {
    return _localStorage.getValue(
      _KEY_DANMAKU_FIXED_TIME,
      defaultValue: defaultVal ?? DEFAULT_DANMAKU_FIXED_TIME,
    );
  }

  // ==================== 弹幕密度 ====================
  static final String _KEY_DANMAKU_DENSITY = "KEY_DANMAKU_DENSITY";

  static void saveDanmakuDensity(int density) {
    _localStorage.setValue(_KEY_DANMAKU_DENSITY, density);
  }

  static int loadDanmakuDensity({int? defaultVal}) {
    return _localStorage.getValue(
      _KEY_DANMAKU_DENSITY,
      defaultValue: defaultVal ?? DEFAULT_DANMAKU_DENSITY,
    );
  }

  // ==================== 弹幕屏蔽模式列表 ====================
  static final String _KEY_DANMAKU_BLOCK_MODE_LIST = "KEY_DANMAKU_BLOCK_MODE_LIST";

  static void saveDanmakuBlockModeList(List<String> modeList) {
    _localStorage.setValue(_KEY_DANMAKU_BLOCK_MODE_LIST, modeList);
  }

  static List<String> loadDanmakuBlockModeList({List<String>? defaultVal}) {
    return _localStorage.getValue(
      _KEY_DANMAKU_BLOCK_MODE_LIST,
      defaultValue: defaultVal ?? DEFAULT_DANMAKU_BLOCK_MODE_LIST,
    );
  }

  // ==================== 滚动弹幕显示区域 ====================
  static final String _KEY_DANMAKU_SCROLL_AREA = "KEY_DANMAKU_SCROLL_AREA";

  static void saveDanmakuScrollArea(double area) {
    _localStorage.setValue(_KEY_DANMAKU_SCROLL_AREA, area);
  }

  static double loadDanmakuScrollArea({double? defaultVal}) {
    return _localStorage.getValue(
      _KEY_DANMAKU_SCROLL_AREA,
      defaultValue: defaultVal ?? DEFAULT_DANMAKU_SCROLL_AREA,
    );
  }

  // ==================== 全部弹幕显示区域 ====================
  static final String _KEY_DANMAKU_ALL_AREA = "KEY_DANMAKU_ALL_AREA";

  static void saveDanmakuAllArea(double area) {
    _localStorage.setValue(_KEY_DANMAKU_ALL_AREA, area);
  }

  static double loadDanmakuAllArea({double? defaultVal}) {
    return _localStorage.getValue(
      _KEY_DANMAKU_ALL_AREA,
      defaultValue: defaultVal ?? DEFAULT_DANMAKU_ALL_AREA,
    );
  }

  // ==================== 分辨率宽度 ====================
  static final String _KEY_RESOLUTION_WIDTH = "KEY_RESOLUTION_WIDTH";

  static void saveResolutionWidth(int width) {
    _localStorage.setValue(_KEY_RESOLUTION_WIDTH, width);
  }

  static int loadResolutionWidth({int? defaultVal}) {
    return _localStorage.getValue(
      _KEY_RESOLUTION_WIDTH,
      defaultValue: defaultVal ?? DEFAULT_RESOLUTION_WIDTH,
    );
  }

  // ==================== 分辨率高度 ====================
  static final String _KEY_RESOLUTION_HEIGHT = "KEY_RESOLUTION_HEIGHT";

  static void saveResolutionHeight(int height) {
    _localStorage.setValue(_KEY_RESOLUTION_HEIGHT, height);
  }

  static int loadResolutionHeight({int? defaultVal}) {
    return _localStorage.getValue(
      _KEY_RESOLUTION_HEIGHT,
      defaultValue: defaultVal ?? DEFAULT_RESOLUTION_HEIGHT,
    );
  }


}