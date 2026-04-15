// GENERATED CODE - DO NOT MODIFY BY HAND

part of 'sync_file_provider.dart';

// **************************************************************************
// RiverpodGenerator
// **************************************************************************

// GENERATED CODE - DO NOT MODIFY BY HAND
// ignore_for_file: type=lint, type=warning

@ProviderFor(SyncFileNotifier)
final syncFileProvider = SyncFileNotifierProvider._();

final class SyncFileNotifierProvider
    extends $NotifierProvider<SyncFileNotifier, SyncFileState> {
  SyncFileNotifierProvider._()
    : super(
        from: null,
        argument: null,
        retry: null,
        name: r'syncFileProvider',
        isAutoDispose: true,
        dependencies: null,
        $allTransitiveDependencies: null,
      );

  @override
  String debugGetCreateSourceHash() => _$syncFileNotifierHash();

  @$internal
  @override
  SyncFileNotifier create() => SyncFileNotifier();

  /// {@macro riverpod.override_with_value}
  Override overrideWithValue(SyncFileState value) {
    return $ProviderOverride(
      origin: this,
      providerOverride: $SyncValueProvider<SyncFileState>(value),
    );
  }
}

String _$syncFileNotifierHash() => r'9e529227d11ea8f5b17bc30eba950f6d0a6b9fa1';

abstract class _$SyncFileNotifier extends $Notifier<SyncFileState> {
  SyncFileState build();
  @$mustCallSuper
  @override
  void runBuild() {
    final ref = this.ref as $Ref<SyncFileState, SyncFileState>;
    final element =
        ref.element
            as $ClassProviderElement<
              AnyNotifier<SyncFileState, SyncFileState>,
              SyncFileState,
              Object?,
              Object?
            >;
    element.handleCreate(ref, build);
  }
}
