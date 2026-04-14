// GENERATED CODE - DO NOT MODIFY BY HAND
// coverage:ignore-file
// ignore_for_file: type=lint
// ignore_for_file: unused_element, deprecated_member_use, deprecated_member_use_from_same_package, use_function_type_syntax_for_parameters, unnecessary_const, avoid_init_to_null, invalid_override_different_default_values_named, prefer_expression_function_bodies, annotate_overrides, invalid_annotation_target, unnecessary_question_mark

part of 'file_state.dart';

// **************************************************************************
// FreezedGenerator
// **************************************************************************

// dart format off
T _$identity<T>(T value) => value;
/// @nodoc
mixin _$FileState {

 List<OutputFileItemBean> get outputFileItems; Directory? get outputDir; String? get errMsg;
/// Create a copy of FileState
/// with the given fields replaced by the non-null parameter values.
@JsonKey(includeFromJson: false, includeToJson: false)
@pragma('vm:prefer-inline')
$FileStateCopyWith<FileState> get copyWith => _$FileStateCopyWithImpl<FileState>(this as FileState, _$identity);



@override
bool operator ==(Object other) {
  return identical(this, other) || (other.runtimeType == runtimeType&&other is FileState&&const DeepCollectionEquality().equals(other.outputFileItems, outputFileItems)&&(identical(other.outputDir, outputDir) || other.outputDir == outputDir)&&(identical(other.errMsg, errMsg) || other.errMsg == errMsg));
}


@override
int get hashCode => Object.hash(runtimeType,const DeepCollectionEquality().hash(outputFileItems),outputDir,errMsg);

@override
String toString() {
  return 'FileState(outputFileItems: $outputFileItems, outputDir: $outputDir, errMsg: $errMsg)';
}


}

/// @nodoc
abstract mixin class $FileStateCopyWith<$Res>  {
  factory $FileStateCopyWith(FileState value, $Res Function(FileState) _then) = _$FileStateCopyWithImpl;
@useResult
$Res call({
 List<OutputFileItemBean> outputFileItems, Directory? outputDir, String? errMsg
});




}
/// @nodoc
class _$FileStateCopyWithImpl<$Res>
    implements $FileStateCopyWith<$Res> {
  _$FileStateCopyWithImpl(this._self, this._then);

  final FileState _self;
  final $Res Function(FileState) _then;

/// Create a copy of FileState
/// with the given fields replaced by the non-null parameter values.
@pragma('vm:prefer-inline') @override $Res call({Object? outputFileItems = null,Object? outputDir = freezed,Object? errMsg = freezed,}) {
  return _then(_self.copyWith(
outputFileItems: null == outputFileItems ? _self.outputFileItems : outputFileItems // ignore: cast_nullable_to_non_nullable
as List<OutputFileItemBean>,outputDir: freezed == outputDir ? _self.outputDir : outputDir // ignore: cast_nullable_to_non_nullable
as Directory?,errMsg: freezed == errMsg ? _self.errMsg : errMsg // ignore: cast_nullable_to_non_nullable
as String?,
  ));
}

}


/// Adds pattern-matching-related methods to [FileState].
extension FileStatePatterns on FileState {
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

@optionalTypeArgs TResult maybeMap<TResult extends Object?>(TResult Function( _FileState value)?  $default,{required TResult orElse(),}){
final _that = this;
switch (_that) {
case _FileState() when $default != null:
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

@optionalTypeArgs TResult map<TResult extends Object?>(TResult Function( _FileState value)  $default,){
final _that = this;
switch (_that) {
case _FileState():
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

@optionalTypeArgs TResult? mapOrNull<TResult extends Object?>(TResult? Function( _FileState value)?  $default,){
final _that = this;
switch (_that) {
case _FileState() when $default != null:
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

@optionalTypeArgs TResult maybeWhen<TResult extends Object?>(TResult Function( List<OutputFileItemBean> outputFileItems,  Directory? outputDir,  String? errMsg)?  $default,{required TResult orElse(),}) {final _that = this;
switch (_that) {
case _FileState() when $default != null:
return $default(_that.outputFileItems,_that.outputDir,_that.errMsg);case _:
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

@optionalTypeArgs TResult when<TResult extends Object?>(TResult Function( List<OutputFileItemBean> outputFileItems,  Directory? outputDir,  String? errMsg)  $default,) {final _that = this;
switch (_that) {
case _FileState():
return $default(_that.outputFileItems,_that.outputDir,_that.errMsg);case _:
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

@optionalTypeArgs TResult? whenOrNull<TResult extends Object?>(TResult? Function( List<OutputFileItemBean> outputFileItems,  Directory? outputDir,  String? errMsg)?  $default,) {final _that = this;
switch (_that) {
case _FileState() when $default != null:
return $default(_that.outputFileItems,_that.outputDir,_that.errMsg);case _:
  return null;

}
}

}

/// @nodoc


class _FileState extends FileState {
  const _FileState({final  List<OutputFileItemBean> outputFileItems = const [], this.outputDir, this.errMsg}): _outputFileItems = outputFileItems,super._();
  

 final  List<OutputFileItemBean> _outputFileItems;
@override@JsonKey() List<OutputFileItemBean> get outputFileItems {
  if (_outputFileItems is EqualUnmodifiableListView) return _outputFileItems;
  // ignore: implicit_dynamic_type
  return EqualUnmodifiableListView(_outputFileItems);
}

@override final  Directory? outputDir;
@override final  String? errMsg;

/// Create a copy of FileState
/// with the given fields replaced by the non-null parameter values.
@override @JsonKey(includeFromJson: false, includeToJson: false)
@pragma('vm:prefer-inline')
_$FileStateCopyWith<_FileState> get copyWith => __$FileStateCopyWithImpl<_FileState>(this, _$identity);



@override
bool operator ==(Object other) {
  return identical(this, other) || (other.runtimeType == runtimeType&&other is _FileState&&const DeepCollectionEquality().equals(other._outputFileItems, _outputFileItems)&&(identical(other.outputDir, outputDir) || other.outputDir == outputDir)&&(identical(other.errMsg, errMsg) || other.errMsg == errMsg));
}


@override
int get hashCode => Object.hash(runtimeType,const DeepCollectionEquality().hash(_outputFileItems),outputDir,errMsg);

@override
String toString() {
  return 'FileState(outputFileItems: $outputFileItems, outputDir: $outputDir, errMsg: $errMsg)';
}


}

/// @nodoc
abstract mixin class _$FileStateCopyWith<$Res> implements $FileStateCopyWith<$Res> {
  factory _$FileStateCopyWith(_FileState value, $Res Function(_FileState) _then) = __$FileStateCopyWithImpl;
@override @useResult
$Res call({
 List<OutputFileItemBean> outputFileItems, Directory? outputDir, String? errMsg
});




}
/// @nodoc
class __$FileStateCopyWithImpl<$Res>
    implements _$FileStateCopyWith<$Res> {
  __$FileStateCopyWithImpl(this._self, this._then);

  final _FileState _self;
  final $Res Function(_FileState) _then;

/// Create a copy of FileState
/// with the given fields replaced by the non-null parameter values.
@override @pragma('vm:prefer-inline') $Res call({Object? outputFileItems = null,Object? outputDir = freezed,Object? errMsg = freezed,}) {
  return _then(_FileState(
outputFileItems: null == outputFileItems ? _self._outputFileItems : outputFileItems // ignore: cast_nullable_to_non_nullable
as List<OutputFileItemBean>,outputDir: freezed == outputDir ? _self.outputDir : outputDir // ignore: cast_nullable_to_non_nullable
as Directory?,errMsg: freezed == errMsg ? _self.errMsg : errMsg // ignore: cast_nullable_to_non_nullable
as String?,
  ));
}


}

// dart format on
