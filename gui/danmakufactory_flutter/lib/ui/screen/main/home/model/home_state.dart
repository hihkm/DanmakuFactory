import 'package:freezed_annotation/freezed_annotation.dart';

part 'home_state.freezed.dart';

@freezed
abstract class HomeState with _$HomeState {
  const HomeState._();

  const factory HomeState({
    @Default(DanmakuFormat.json) DanmakuFormat outputDanmakuFormat,
    @Default([]) List<String> inputFiles,
    String? errMsg,
  }) = _HomeState;
}

/// 弹幕格式
enum DanmakuFormat {
  ass("ASS", "ass"),
  xml("XML", "xml"),
  json("JSON", "json");

  final String title;
  final String value;

  const DanmakuFormat(this.title, this.value);
}
