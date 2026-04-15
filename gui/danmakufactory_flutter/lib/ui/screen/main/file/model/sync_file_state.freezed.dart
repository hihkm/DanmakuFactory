// GENERATED CODE - DO NOT MODIFY BY HAND
// coverage:ignore-file
// ignore_for_file: type=lint
// ignore_for_file: unused_element, deprecated_member_use, deprecated_member_use_from_same_package, use_function_type_syntax_for_parameters, unnecessary_const, avoid_init_to_null, invalid_override_different_default_values_named, prefer_expression_function_bodies, annotate_overrides, invalid_annotation_target, unnecessary_question_mark

part of 'sync_file_state.dart';

// **************************************************************************
// FreezedGenerator
// **************************************************************************

// dart format off
T _$identity<T>(T value) => value;
/// @nodoc
mixin _$SyncFileState {

 bool get isManageModel; String? get errMsg;
/// Create a copy of SyncFileState
/// with the given fields replaced by the non-null parameter values.
@JsonKey(includeFromJson: false, includeToJson: false)
@pragma('vm:prefer-inline')
$SyncFileStateCopyWith<SyncFileState> get copyWith => _$SyncFileStateCopyWithImpl<SyncFileState>(this as SyncFileState, _$identity);



@override
bool operator ==(Object other) {
  return identical(this, other) || (other.runtimeType == runtimeType&&other is SyncFileState&&(identical(other.isManageModel, isManageModel) || other.isManageModel == isManageModel)&&(identical(other.errMsg, errMsg) || other.errMsg == errMsg));
}


@override
int get hashCode => Object.hash(runtimeType,isManageModel,errMsg);

@override
String toString() {
  return 'SyncFileState(isManageModel: $isManageModel, errMsg: $errMsg)';
}


}

/// @nodoc
abstract mixin class $SyncFileStateCopyWith<$Res>  {
  factory $SyncFileStateCopyWith(SyncFileState value, $Res Function(SyncFileState) _then) = _$SyncFileStateCopyWithImpl;
@useResult
$Res call({
 bool isManageModel, String? errMsg
});




}
/// @nodoc
class _$SyncFileStateCopyWithImpl<$Res>
    implements $SyncFileStateCopyWith<$Res> {
  _$SyncFileStateCopyWithImpl(this._self, this._then);

  final SyncFileState _self;
  final $Res Function(SyncFileState) _then;

/// Create a copy of SyncFileState
/// with the given fields replaced by the non-null parameter values.
@pragma('vm:prefer-inline') @override $Res call({Object? isManageModel = null,Object? errMsg = freezed,}) {
  return _then(_self.copyWith(
isManageModel: null == isManageModel ? _self.isManageModel : isManageModel // ignore: cast_nullable_to_non_nullable
as bool,errMsg: freezed == errMsg ? _self.errMsg : errMsg // ignore: cast_nullable_to_non_nullable
as String?,
  ));
}

}


/// Adds pattern-matching-related methods to [SyncFileState].
extension SyncFileStatePatterns on SyncFileState {
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

@optionalTypeArgs TResult maybeMap<TResult extends Object?>(TResult Function( _SyncFileState value)?  $default,{required TResult orElse(),}){
final _that = this;
switch (_that) {
case _SyncFileState() when $default != null:
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

@optionalTypeArgs TResult map<TResult extends Object?>(TResult Function( _SyncFileState value)  $default,){
final _that = this;
switch (_that) {
case _SyncFileState():
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

@optionalTypeArgs TResult? mapOrNull<TResult extends Object?>(TResult? Function( _SyncFileState value)?  $default,){
final _that = this;
switch (_that) {
case _SyncFileState() when $default != null:
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

@optionalTypeArgs TResult maybeWhen<TResult extends Object?>(TResult Function( bool isManageModel,  String? errMsg)?  $default,{required TResult orElse(),}) {final _that = this;
switch (_that) {
case _SyncFileState() when $default != null:
return $default(_that.isManageModel,_that.errMsg);case _:
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

@optionalTypeArgs TResult when<TResult extends Object?>(TResult Function( bool isManageModel,  String? errMsg)  $default,) {final _that = this;
switch (_that) {
case _SyncFileState():
return $default(_that.isManageModel,_that.errMsg);case _:
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

@optionalTypeArgs TResult? whenOrNull<TResult extends Object?>(TResult? Function( bool isManageModel,  String? errMsg)?  $default,) {final _that = this;
switch (_that) {
case _SyncFileState() when $default != null:
return $default(_that.isManageModel,_that.errMsg);case _:
  return null;

}
}

}

/// @nodoc


class _SyncFileState extends SyncFileState {
  const _SyncFileState({this.isManageModel = false, this.errMsg}): super._();
  

@override@JsonKey() final  bool isManageModel;
@override final  String? errMsg;

/// Create a copy of SyncFileState
/// with the given fields replaced by the non-null parameter values.
@override @JsonKey(includeFromJson: false, includeToJson: false)
@pragma('vm:prefer-inline')
_$SyncFileStateCopyWith<_SyncFileState> get copyWith => __$SyncFileStateCopyWithImpl<_SyncFileState>(this, _$identity);



@override
bool operator ==(Object other) {
  return identical(this, other) || (other.runtimeType == runtimeType&&other is _SyncFileState&&(identical(other.isManageModel, isManageModel) || other.isManageModel == isManageModel)&&(identical(other.errMsg, errMsg) || other.errMsg == errMsg));
}


@override
int get hashCode => Object.hash(runtimeType,isManageModel,errMsg);

@override
String toString() {
  return 'SyncFileState(isManageModel: $isManageModel, errMsg: $errMsg)';
}


}

/// @nodoc
abstract mixin class _$SyncFileStateCopyWith<$Res> implements $SyncFileStateCopyWith<$Res> {
  factory _$SyncFileStateCopyWith(_SyncFileState value, $Res Function(_SyncFileState) _then) = __$SyncFileStateCopyWithImpl;
@override @useResult
$Res call({
 bool isManageModel, String? errMsg
});




}
/// @nodoc
class __$SyncFileStateCopyWithImpl<$Res>
    implements _$SyncFileStateCopyWith<$Res> {
  __$SyncFileStateCopyWithImpl(this._self, this._then);

  final _SyncFileState _self;
  final $Res Function(_SyncFileState) _then;

/// Create a copy of SyncFileState
/// with the given fields replaced by the non-null parameter values.
@override @pragma('vm:prefer-inline') $Res call({Object? isManageModel = null,Object? errMsg = freezed,}) {
  return _then(_SyncFileState(
isManageModel: null == isManageModel ? _self.isManageModel : isManageModel // ignore: cast_nullable_to_non_nullable
as bool,errMsg: freezed == errMsg ? _self.errMsg : errMsg // ignore: cast_nullable_to_non_nullable
as String?,
  ));
}


}

// dart format on
