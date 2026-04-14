// GENERATED CODE - DO NOT MODIFY BY HAND
// coverage:ignore-file
// ignore_for_file: type=lint
// ignore_for_file: unused_element, deprecated_member_use, deprecated_member_use_from_same_package, use_function_type_syntax_for_parameters, unnecessary_const, avoid_init_to_null, invalid_override_different_default_values_named, prefer_expression_function_bodies, annotate_overrides, invalid_annotation_target, unnecessary_question_mark

part of 'home_state.dart';

// **************************************************************************
// FreezedGenerator
// **************************************************************************

// dart format off
T _$identity<T>(T value) => value;
/// @nodoc
mixin _$HomeState {

 DanmakuFormat get outputDanmakuFormat; List<String> get inputFiles; String? get errMsg;
/// Create a copy of HomeState
/// with the given fields replaced by the non-null parameter values.
@JsonKey(includeFromJson: false, includeToJson: false)
@pragma('vm:prefer-inline')
$HomeStateCopyWith<HomeState> get copyWith => _$HomeStateCopyWithImpl<HomeState>(this as HomeState, _$identity);



@override
bool operator ==(Object other) {
  return identical(this, other) || (other.runtimeType == runtimeType&&other is HomeState&&(identical(other.outputDanmakuFormat, outputDanmakuFormat) || other.outputDanmakuFormat == outputDanmakuFormat)&&const DeepCollectionEquality().equals(other.inputFiles, inputFiles)&&(identical(other.errMsg, errMsg) || other.errMsg == errMsg));
}


@override
int get hashCode => Object.hash(runtimeType,outputDanmakuFormat,const DeepCollectionEquality().hash(inputFiles),errMsg);

@override
String toString() {
  return 'HomeState(outputDanmakuFormat: $outputDanmakuFormat, inputFiles: $inputFiles, errMsg: $errMsg)';
}


}

/// @nodoc
abstract mixin class $HomeStateCopyWith<$Res>  {
  factory $HomeStateCopyWith(HomeState value, $Res Function(HomeState) _then) = _$HomeStateCopyWithImpl;
@useResult
$Res call({
 DanmakuFormat outputDanmakuFormat, List<String> inputFiles, String? errMsg
});




}
/// @nodoc
class _$HomeStateCopyWithImpl<$Res>
    implements $HomeStateCopyWith<$Res> {
  _$HomeStateCopyWithImpl(this._self, this._then);

  final HomeState _self;
  final $Res Function(HomeState) _then;

/// Create a copy of HomeState
/// with the given fields replaced by the non-null parameter values.
@pragma('vm:prefer-inline') @override $Res call({Object? outputDanmakuFormat = null,Object? inputFiles = null,Object? errMsg = freezed,}) {
  return _then(_self.copyWith(
outputDanmakuFormat: null == outputDanmakuFormat ? _self.outputDanmakuFormat : outputDanmakuFormat // ignore: cast_nullable_to_non_nullable
as DanmakuFormat,inputFiles: null == inputFiles ? _self.inputFiles : inputFiles // ignore: cast_nullable_to_non_nullable
as List<String>,errMsg: freezed == errMsg ? _self.errMsg : errMsg // ignore: cast_nullable_to_non_nullable
as String?,
  ));
}

}


/// Adds pattern-matching-related methods to [HomeState].
extension HomeStatePatterns on HomeState {
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

@optionalTypeArgs TResult maybeMap<TResult extends Object?>(TResult Function( _HomeState value)?  $default,{required TResult orElse(),}){
final _that = this;
switch (_that) {
case _HomeState() when $default != null:
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

@optionalTypeArgs TResult map<TResult extends Object?>(TResult Function( _HomeState value)  $default,){
final _that = this;
switch (_that) {
case _HomeState():
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

@optionalTypeArgs TResult? mapOrNull<TResult extends Object?>(TResult? Function( _HomeState value)?  $default,){
final _that = this;
switch (_that) {
case _HomeState() when $default != null:
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

@optionalTypeArgs TResult maybeWhen<TResult extends Object?>(TResult Function( DanmakuFormat outputDanmakuFormat,  List<String> inputFiles,  String? errMsg)?  $default,{required TResult orElse(),}) {final _that = this;
switch (_that) {
case _HomeState() when $default != null:
return $default(_that.outputDanmakuFormat,_that.inputFiles,_that.errMsg);case _:
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

@optionalTypeArgs TResult when<TResult extends Object?>(TResult Function( DanmakuFormat outputDanmakuFormat,  List<String> inputFiles,  String? errMsg)  $default,) {final _that = this;
switch (_that) {
case _HomeState():
return $default(_that.outputDanmakuFormat,_that.inputFiles,_that.errMsg);case _:
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

@optionalTypeArgs TResult? whenOrNull<TResult extends Object?>(TResult? Function( DanmakuFormat outputDanmakuFormat,  List<String> inputFiles,  String? errMsg)?  $default,) {final _that = this;
switch (_that) {
case _HomeState() when $default != null:
return $default(_that.outputDanmakuFormat,_that.inputFiles,_that.errMsg);case _:
  return null;

}
}

}

/// @nodoc


class _HomeState extends HomeState {
  const _HomeState({this.outputDanmakuFormat = DanmakuFormat.json, final  List<String> inputFiles = const [], this.errMsg}): _inputFiles = inputFiles,super._();
  

@override@JsonKey() final  DanmakuFormat outputDanmakuFormat;
 final  List<String> _inputFiles;
@override@JsonKey() List<String> get inputFiles {
  if (_inputFiles is EqualUnmodifiableListView) return _inputFiles;
  // ignore: implicit_dynamic_type
  return EqualUnmodifiableListView(_inputFiles);
}

@override final  String? errMsg;

/// Create a copy of HomeState
/// with the given fields replaced by the non-null parameter values.
@override @JsonKey(includeFromJson: false, includeToJson: false)
@pragma('vm:prefer-inline')
_$HomeStateCopyWith<_HomeState> get copyWith => __$HomeStateCopyWithImpl<_HomeState>(this, _$identity);



@override
bool operator ==(Object other) {
  return identical(this, other) || (other.runtimeType == runtimeType&&other is _HomeState&&(identical(other.outputDanmakuFormat, outputDanmakuFormat) || other.outputDanmakuFormat == outputDanmakuFormat)&&const DeepCollectionEquality().equals(other._inputFiles, _inputFiles)&&(identical(other.errMsg, errMsg) || other.errMsg == errMsg));
}


@override
int get hashCode => Object.hash(runtimeType,outputDanmakuFormat,const DeepCollectionEquality().hash(_inputFiles),errMsg);

@override
String toString() {
  return 'HomeState(outputDanmakuFormat: $outputDanmakuFormat, inputFiles: $inputFiles, errMsg: $errMsg)';
}


}

/// @nodoc
abstract mixin class _$HomeStateCopyWith<$Res> implements $HomeStateCopyWith<$Res> {
  factory _$HomeStateCopyWith(_HomeState value, $Res Function(_HomeState) _then) = __$HomeStateCopyWithImpl;
@override @useResult
$Res call({
 DanmakuFormat outputDanmakuFormat, List<String> inputFiles, String? errMsg
});




}
/// @nodoc
class __$HomeStateCopyWithImpl<$Res>
    implements _$HomeStateCopyWith<$Res> {
  __$HomeStateCopyWithImpl(this._self, this._then);

  final _HomeState _self;
  final $Res Function(_HomeState) _then;

/// Create a copy of HomeState
/// with the given fields replaced by the non-null parameter values.
@override @pragma('vm:prefer-inline') $Res call({Object? outputDanmakuFormat = null,Object? inputFiles = null,Object? errMsg = freezed,}) {
  return _then(_HomeState(
outputDanmakuFormat: null == outputDanmakuFormat ? _self.outputDanmakuFormat : outputDanmakuFormat // ignore: cast_nullable_to_non_nullable
as DanmakuFormat,inputFiles: null == inputFiles ? _self._inputFiles : inputFiles // ignore: cast_nullable_to_non_nullable
as List<String>,errMsg: freezed == errMsg ? _self.errMsg : errMsg // ignore: cast_nullable_to_non_nullable
as String?,
  ));
}


}

// dart format on
