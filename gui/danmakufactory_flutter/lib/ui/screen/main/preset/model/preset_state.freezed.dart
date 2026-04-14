// GENERATED CODE - DO NOT MODIFY BY HAND
// coverage:ignore-file
// ignore_for_file: type=lint
// ignore_for_file: unused_element, deprecated_member_use, deprecated_member_use_from_same_package, use_function_type_syntax_for_parameters, unnecessary_const, avoid_init_to_null, invalid_override_different_default_values_named, prefer_expression_function_bodies, annotate_overrides, invalid_annotation_target, unnecessary_question_mark

part of 'preset_state.dart';

// **************************************************************************
// FreezedGenerator
// **************************************************************************

// dart format off
T _$identity<T>(T value) => value;
/// @nodoc
mixin _$PresetState {

//文本大小
 int get textSize;//文本阴影:0-4 整数
 int get textShadow;//文本透明度:0-255 整数
 int get textOpacity;//文本描边:0-4 整数
 int get textOutline;//是否粗体
 bool get isBold;//滚动弹幕通过时间
 double get danmakuScrollTime;//固定弹幕停留时间
 double get danmakuFixedTime;//弹幕密度:-1 不重叠,0 无限制,其他 表示限定条数
 int get danmakuDensity;//弹幕屏蔽模式列表:要屏蔽的弹幕类型名称，用-连接:L2R, R2L, TOP, BOTTOM, SPECIAL, COLOR, REPEAT
 List<String> get danmakuBlockModeList;//滚动弹幕显示区域:0.0-1.0 浮点数
 double get danmakuScrollArea;//全部弹幕显示区域:0.0-1.0 浮点数
 double get danmakuAllArea;//分辨率宽 度
 int get resolutionWidth;// 分辨率高度
 int get resolutionHeight;// 错误信息
 String? get errMsg;
/// Create a copy of PresetState
/// with the given fields replaced by the non-null parameter values.
@JsonKey(includeFromJson: false, includeToJson: false)
@pragma('vm:prefer-inline')
$PresetStateCopyWith<PresetState> get copyWith => _$PresetStateCopyWithImpl<PresetState>(this as PresetState, _$identity);



@override
bool operator ==(Object other) {
  return identical(this, other) || (other.runtimeType == runtimeType&&other is PresetState&&(identical(other.textSize, textSize) || other.textSize == textSize)&&(identical(other.textShadow, textShadow) || other.textShadow == textShadow)&&(identical(other.textOpacity, textOpacity) || other.textOpacity == textOpacity)&&(identical(other.textOutline, textOutline) || other.textOutline == textOutline)&&(identical(other.isBold, isBold) || other.isBold == isBold)&&(identical(other.danmakuScrollTime, danmakuScrollTime) || other.danmakuScrollTime == danmakuScrollTime)&&(identical(other.danmakuFixedTime, danmakuFixedTime) || other.danmakuFixedTime == danmakuFixedTime)&&(identical(other.danmakuDensity, danmakuDensity) || other.danmakuDensity == danmakuDensity)&&const DeepCollectionEquality().equals(other.danmakuBlockModeList, danmakuBlockModeList)&&(identical(other.danmakuScrollArea, danmakuScrollArea) || other.danmakuScrollArea == danmakuScrollArea)&&(identical(other.danmakuAllArea, danmakuAllArea) || other.danmakuAllArea == danmakuAllArea)&&(identical(other.resolutionWidth, resolutionWidth) || other.resolutionWidth == resolutionWidth)&&(identical(other.resolutionHeight, resolutionHeight) || other.resolutionHeight == resolutionHeight)&&(identical(other.errMsg, errMsg) || other.errMsg == errMsg));
}


@override
int get hashCode => Object.hash(runtimeType,textSize,textShadow,textOpacity,textOutline,isBold,danmakuScrollTime,danmakuFixedTime,danmakuDensity,const DeepCollectionEquality().hash(danmakuBlockModeList),danmakuScrollArea,danmakuAllArea,resolutionWidth,resolutionHeight,errMsg);

@override
String toString() {
  return 'PresetState(textSize: $textSize, textShadow: $textShadow, textOpacity: $textOpacity, textOutline: $textOutline, isBold: $isBold, danmakuScrollTime: $danmakuScrollTime, danmakuFixedTime: $danmakuFixedTime, danmakuDensity: $danmakuDensity, danmakuBlockModeList: $danmakuBlockModeList, danmakuScrollArea: $danmakuScrollArea, danmakuAllArea: $danmakuAllArea, resolutionWidth: $resolutionWidth, resolutionHeight: $resolutionHeight, errMsg: $errMsg)';
}


}

/// @nodoc
abstract mixin class $PresetStateCopyWith<$Res>  {
  factory $PresetStateCopyWith(PresetState value, $Res Function(PresetState) _then) = _$PresetStateCopyWithImpl;
@useResult
$Res call({
 int textSize, int textShadow, int textOpacity, int textOutline, bool isBold, double danmakuScrollTime, double danmakuFixedTime, int danmakuDensity, List<String> danmakuBlockModeList, double danmakuScrollArea, double danmakuAllArea, int resolutionWidth, int resolutionHeight, String? errMsg
});




}
/// @nodoc
class _$PresetStateCopyWithImpl<$Res>
    implements $PresetStateCopyWith<$Res> {
  _$PresetStateCopyWithImpl(this._self, this._then);

  final PresetState _self;
  final $Res Function(PresetState) _then;

/// Create a copy of PresetState
/// with the given fields replaced by the non-null parameter values.
@pragma('vm:prefer-inline') @override $Res call({Object? textSize = null,Object? textShadow = null,Object? textOpacity = null,Object? textOutline = null,Object? isBold = null,Object? danmakuScrollTime = null,Object? danmakuFixedTime = null,Object? danmakuDensity = null,Object? danmakuBlockModeList = null,Object? danmakuScrollArea = null,Object? danmakuAllArea = null,Object? resolutionWidth = null,Object? resolutionHeight = null,Object? errMsg = freezed,}) {
  return _then(_self.copyWith(
textSize: null == textSize ? _self.textSize : textSize // ignore: cast_nullable_to_non_nullable
as int,textShadow: null == textShadow ? _self.textShadow : textShadow // ignore: cast_nullable_to_non_nullable
as int,textOpacity: null == textOpacity ? _self.textOpacity : textOpacity // ignore: cast_nullable_to_non_nullable
as int,textOutline: null == textOutline ? _self.textOutline : textOutline // ignore: cast_nullable_to_non_nullable
as int,isBold: null == isBold ? _self.isBold : isBold // ignore: cast_nullable_to_non_nullable
as bool,danmakuScrollTime: null == danmakuScrollTime ? _self.danmakuScrollTime : danmakuScrollTime // ignore: cast_nullable_to_non_nullable
as double,danmakuFixedTime: null == danmakuFixedTime ? _self.danmakuFixedTime : danmakuFixedTime // ignore: cast_nullable_to_non_nullable
as double,danmakuDensity: null == danmakuDensity ? _self.danmakuDensity : danmakuDensity // ignore: cast_nullable_to_non_nullable
as int,danmakuBlockModeList: null == danmakuBlockModeList ? _self.danmakuBlockModeList : danmakuBlockModeList // ignore: cast_nullable_to_non_nullable
as List<String>,danmakuScrollArea: null == danmakuScrollArea ? _self.danmakuScrollArea : danmakuScrollArea // ignore: cast_nullable_to_non_nullable
as double,danmakuAllArea: null == danmakuAllArea ? _self.danmakuAllArea : danmakuAllArea // ignore: cast_nullable_to_non_nullable
as double,resolutionWidth: null == resolutionWidth ? _self.resolutionWidth : resolutionWidth // ignore: cast_nullable_to_non_nullable
as int,resolutionHeight: null == resolutionHeight ? _self.resolutionHeight : resolutionHeight // ignore: cast_nullable_to_non_nullable
as int,errMsg: freezed == errMsg ? _self.errMsg : errMsg // ignore: cast_nullable_to_non_nullable
as String?,
  ));
}

}


/// Adds pattern-matching-related methods to [PresetState].
extension PresetStatePatterns on PresetState {
/// A variant of `map` that fallback to returning `orElse`.
///
/// It is equivalent to doing:
/// ```dart
/// switch (sealedClass) {
///   case final Subclass value:
///     return ...;
///   case _:
///     return orElse();
/// }
/// ```

@optionalTypeArgs TResult maybeMap<TResult extends Object?>(TResult Function( _PresetState value)?  $default,{required TResult orElse(),}){
final _that = this;
switch (_that) {
case _PresetState() when $default != null:
return $default(_that);case _:
  return orElse();

}
}
/// A `switch`-like method, using callbacks.
///
/// Callbacks receives the raw object, upcasted.
/// It is equivalent to doing:
/// ```dart
/// switch (sealedClass) {
///   case final Subclass value:
///     return ...;
///   case final Subclass2 value:
///     return ...;
/// }
/// ```

@optionalTypeArgs TResult map<TResult extends Object?>(TResult Function( _PresetState value)  $default,){
final _that = this;
switch (_that) {
case _PresetState():
return $default(_that);case _:
  throw StateError('Unexpected subclass');

}
}
/// A variant of `map` that fallback to returning `null`.
///
/// It is equivalent to doing:
/// ```dart
/// switch (sealedClass) {
///   case final Subclass value:
///     return ...;
///   case _:
///     return null;
/// }
/// ```

@optionalTypeArgs TResult? mapOrNull<TResult extends Object?>(TResult? Function( _PresetState value)?  $default,){
final _that = this;
switch (_that) {
case _PresetState() when $default != null:
return $default(_that);case _:
  return null;

}
}
/// A variant of `when` that fallback to an `orElse` callback.
///
/// It is equivalent to doing:
/// ```dart
/// switch (sealedClass) {
///   case Subclass(:final field):
///     return ...;
///   case _:
///     return orElse();
/// }
/// ```

@optionalTypeArgs TResult maybeWhen<TResult extends Object?>(TResult Function( int textSize,  int textShadow,  int textOpacity,  int textOutline,  bool isBold,  double danmakuScrollTime,  double danmakuFixedTime,  int danmakuDensity,  List<String> danmakuBlockModeList,  double danmakuScrollArea,  double danmakuAllArea,  int resolutionWidth,  int resolutionHeight,  String? errMsg)?  $default,{required TResult orElse(),}) {final _that = this;
switch (_that) {
case _PresetState() when $default != null:
return $default(_that.textSize,_that.textShadow,_that.textOpacity,_that.textOutline,_that.isBold,_that.danmakuScrollTime,_that.danmakuFixedTime,_that.danmakuDensity,_that.danmakuBlockModeList,_that.danmakuScrollArea,_that.danmakuAllArea,_that.resolutionWidth,_that.resolutionHeight,_that.errMsg);case _:
  return orElse();

}
}
/// A `switch`-like method, using callbacks.
///
/// As opposed to `map`, this offers destructuring.
/// It is equivalent to doing:
/// ```dart
/// switch (sealedClass) {
///   case Subclass(:final field):
///     return ...;
///   case Subclass2(:final field2):
///     return ...;
/// }
/// ```

@optionalTypeArgs TResult when<TResult extends Object?>(TResult Function( int textSize,  int textShadow,  int textOpacity,  int textOutline,  bool isBold,  double danmakuScrollTime,  double danmakuFixedTime,  int danmakuDensity,  List<String> danmakuBlockModeList,  double danmakuScrollArea,  double danmakuAllArea,  int resolutionWidth,  int resolutionHeight,  String? errMsg)  $default,) {final _that = this;
switch (_that) {
case _PresetState():
return $default(_that.textSize,_that.textShadow,_that.textOpacity,_that.textOutline,_that.isBold,_that.danmakuScrollTime,_that.danmakuFixedTime,_that.danmakuDensity,_that.danmakuBlockModeList,_that.danmakuScrollArea,_that.danmakuAllArea,_that.resolutionWidth,_that.resolutionHeight,_that.errMsg);case _:
  throw StateError('Unexpected subclass');

}
}
/// A variant of `when` that fallback to returning `null`
///
/// It is equivalent to doing:
/// ```dart
/// switch (sealedClass) {
///   case Subclass(:final field):
///     return ...;
///   case _:
///     return null;
/// }
/// ```

@optionalTypeArgs TResult? whenOrNull<TResult extends Object?>(TResult? Function( int textSize,  int textShadow,  int textOpacity,  int textOutline,  bool isBold,  double danmakuScrollTime,  double danmakuFixedTime,  int danmakuDensity,  List<String> danmakuBlockModeList,  double danmakuScrollArea,  double danmakuAllArea,  int resolutionWidth,  int resolutionHeight,  String? errMsg)?  $default,) {final _that = this;
switch (_that) {
case _PresetState() when $default != null:
return $default(_that.textSize,_that.textShadow,_that.textOpacity,_that.textOutline,_that.isBold,_that.danmakuScrollTime,_that.danmakuFixedTime,_that.danmakuDensity,_that.danmakuBlockModeList,_that.danmakuScrollArea,_that.danmakuAllArea,_that.resolutionWidth,_that.resolutionHeight,_that.errMsg);case _:
  return null;

}
}

}

/// @nodoc


class _PresetState extends PresetState {
  const _PresetState({this.textSize = SettingsRepository.DEFAULT_TEXT_SIZE, this.textShadow = SettingsRepository.DEFAULT_TEXT_SHADOW, this.textOpacity = SettingsRepository.DEFAULT_TEXT_OPACITY, this.textOutline = SettingsRepository.DEFAULT_TEXT_OUTLINE, this.isBold = SettingsRepository.DEFAULT_IS_BOLD, this.danmakuScrollTime = SettingsRepository.DEFAULT_DANMAKU_SCROLL_TIME, this.danmakuFixedTime = SettingsRepository.DEFAULT_DANMAKU_FIXED_TIME, this.danmakuDensity = SettingsRepository.DEFAULT_DANMAKU_DENSITY, final  List<String> danmakuBlockModeList = SettingsRepository.DEFAULT_DANMAKU_BLOCK_MODE_LIST, this.danmakuScrollArea = SettingsRepository.DEFAULT_DANMAKU_SCROLL_AREA, this.danmakuAllArea = SettingsRepository.DEFAULT_DANMAKU_ALL_AREA, this.resolutionWidth = SettingsRepository.DEFAULT_RESOLUTION_WIDTH, this.resolutionHeight = SettingsRepository.DEFAULT_RESOLUTION_HEIGHT, this.errMsg}): _danmakuBlockModeList = danmakuBlockModeList,super._();
  

//文本大小
@override@JsonKey() final  int textSize;
//文本阴影:0-4 整数
@override@JsonKey() final  int textShadow;
//文本透明度:0-255 整数
@override@JsonKey() final  int textOpacity;
//文本描边:0-4 整数
@override@JsonKey() final  int textOutline;
//是否粗体
@override@JsonKey() final  bool isBold;
//滚动弹幕通过时间
@override@JsonKey() final  double danmakuScrollTime;
//固定弹幕停留时间
@override@JsonKey() final  double danmakuFixedTime;
//弹幕密度:-1 不重叠,0 无限制,其他 表示限定条数
@override@JsonKey() final  int danmakuDensity;
//弹幕屏蔽模式列表:要屏蔽的弹幕类型名称，用-连接:L2R, R2L, TOP, BOTTOM, SPECIAL, COLOR, REPEAT
 final  List<String> _danmakuBlockModeList;
//弹幕屏蔽模式列表:要屏蔽的弹幕类型名称，用-连接:L2R, R2L, TOP, BOTTOM, SPECIAL, COLOR, REPEAT
@override@JsonKey() List<String> get danmakuBlockModeList {
  if (_danmakuBlockModeList is EqualUnmodifiableListView) return _danmakuBlockModeList;
  // ignore: implicit_dynamic_type
  return EqualUnmodifiableListView(_danmakuBlockModeList);
}

//滚动弹幕显示区域:0.0-1.0 浮点数
@override@JsonKey() final  double danmakuScrollArea;
//全部弹幕显示区域:0.0-1.0 浮点数
@override@JsonKey() final  double danmakuAllArea;
//分辨率宽 度
@override@JsonKey() final  int resolutionWidth;
// 分辨率高度
@override@JsonKey() final  int resolutionHeight;
// 错误信息
@override final  String? errMsg;

/// Create a copy of PresetState
/// with the given fields replaced by the non-null parameter values.
@override @JsonKey(includeFromJson: false, includeToJson: false)
@pragma('vm:prefer-inline')
_$PresetStateCopyWith<_PresetState> get copyWith => __$PresetStateCopyWithImpl<_PresetState>(this, _$identity);



@override
bool operator ==(Object other) {
  return identical(this, other) || (other.runtimeType == runtimeType&&other is _PresetState&&(identical(other.textSize, textSize) || other.textSize == textSize)&&(identical(other.textShadow, textShadow) || other.textShadow == textShadow)&&(identical(other.textOpacity, textOpacity) || other.textOpacity == textOpacity)&&(identical(other.textOutline, textOutline) || other.textOutline == textOutline)&&(identical(other.isBold, isBold) || other.isBold == isBold)&&(identical(other.danmakuScrollTime, danmakuScrollTime) || other.danmakuScrollTime == danmakuScrollTime)&&(identical(other.danmakuFixedTime, danmakuFixedTime) || other.danmakuFixedTime == danmakuFixedTime)&&(identical(other.danmakuDensity, danmakuDensity) || other.danmakuDensity == danmakuDensity)&&const DeepCollectionEquality().equals(other._danmakuBlockModeList, _danmakuBlockModeList)&&(identical(other.danmakuScrollArea, danmakuScrollArea) || other.danmakuScrollArea == danmakuScrollArea)&&(identical(other.danmakuAllArea, danmakuAllArea) || other.danmakuAllArea == danmakuAllArea)&&(identical(other.resolutionWidth, resolutionWidth) || other.resolutionWidth == resolutionWidth)&&(identical(other.resolutionHeight, resolutionHeight) || other.resolutionHeight == resolutionHeight)&&(identical(other.errMsg, errMsg) || other.errMsg == errMsg));
}


@override
int get hashCode => Object.hash(runtimeType,textSize,textShadow,textOpacity,textOutline,isBold,danmakuScrollTime,danmakuFixedTime,danmakuDensity,const DeepCollectionEquality().hash(_danmakuBlockModeList),danmakuScrollArea,danmakuAllArea,resolutionWidth,resolutionHeight,errMsg);

@override
String toString() {
  return 'PresetState(textSize: $textSize, textShadow: $textShadow, textOpacity: $textOpacity, textOutline: $textOutline, isBold: $isBold, danmakuScrollTime: $danmakuScrollTime, danmakuFixedTime: $danmakuFixedTime, danmakuDensity: $danmakuDensity, danmakuBlockModeList: $danmakuBlockModeList, danmakuScrollArea: $danmakuScrollArea, danmakuAllArea: $danmakuAllArea, resolutionWidth: $resolutionWidth, resolutionHeight: $resolutionHeight, errMsg: $errMsg)';
}


}

/// @nodoc
abstract mixin class _$PresetStateCopyWith<$Res> implements $PresetStateCopyWith<$Res> {
  factory _$PresetStateCopyWith(_PresetState value, $Res Function(_PresetState) _then) = __$PresetStateCopyWithImpl;
@override @useResult
$Res call({
 int textSize, int textShadow, int textOpacity, int textOutline, bool isBold, double danmakuScrollTime, double danmakuFixedTime, int danmakuDensity, List<String> danmakuBlockModeList, double danmakuScrollArea, double danmakuAllArea, int resolutionWidth, int resolutionHeight, String? errMsg
});




}
/// @nodoc
class __$PresetStateCopyWithImpl<$Res>
    implements _$PresetStateCopyWith<$Res> {
  __$PresetStateCopyWithImpl(this._self, this._then);

  final _PresetState _self;
  final $Res Function(_PresetState) _then;

/// Create a copy of PresetState
/// with the given fields replaced by the non-null parameter values.
@override @pragma('vm:prefer-inline') $Res call({Object? textSize = null,Object? textShadow = null,Object? textOpacity = null,Object? textOutline = null,Object? isBold = null,Object? danmakuScrollTime = null,Object? danmakuFixedTime = null,Object? danmakuDensity = null,Object? danmakuBlockModeList = null,Object? danmakuScrollArea = null,Object? danmakuAllArea = null,Object? resolutionWidth = null,Object? resolutionHeight = null,Object? errMsg = freezed,}) {
  return _then(_PresetState(
textSize: null == textSize ? _self.textSize : textSize // ignore: cast_nullable_to_non_nullable
as int,textShadow: null == textShadow ? _self.textShadow : textShadow // ignore: cast_nullable_to_non_nullable
as int,textOpacity: null == textOpacity ? _self.textOpacity : textOpacity // ignore: cast_nullable_to_non_nullable
as int,textOutline: null == textOutline ? _self.textOutline : textOutline // ignore: cast_nullable_to_non_nullable
as int,isBold: null == isBold ? _self.isBold : isBold // ignore: cast_nullable_to_non_nullable
as bool,danmakuScrollTime: null == danmakuScrollTime ? _self.danmakuScrollTime : danmakuScrollTime // ignore: cast_nullable_to_non_nullable
as double,danmakuFixedTime: null == danmakuFixedTime ? _self.danmakuFixedTime : danmakuFixedTime // ignore: cast_nullable_to_non_nullable
as double,danmakuDensity: null == danmakuDensity ? _self.danmakuDensity : danmakuDensity // ignore: cast_nullable_to_non_nullable
as int,danmakuBlockModeList: null == danmakuBlockModeList ? _self._danmakuBlockModeList : danmakuBlockModeList // ignore: cast_nullable_to_non_nullable
as List<String>,danmakuScrollArea: null == danmakuScrollArea ? _self.danmakuScrollArea : danmakuScrollArea // ignore: cast_nullable_to_non_nullable
as double,danmakuAllArea: null == danmakuAllArea ? _self.danmakuAllArea : danmakuAllArea // ignore: cast_nullable_to_non_nullable
as double,resolutionWidth: null == resolutionWidth ? _self.resolutionWidth : resolutionWidth // ignore: cast_nullable_to_non_nullable
as int,resolutionHeight: null == resolutionHeight ? _self.resolutionHeight : resolutionHeight // ignore: cast_nullable_to_non_nullable
as int,errMsg: freezed == errMsg ? _self.errMsg : errMsg // ignore: cast_nullable_to_non_nullable
as String?,
  ));
}


}

// dart format on
