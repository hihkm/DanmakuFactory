// GENERATED CODE - DO NOT MODIFY BY HAND

part of 'preset_provider.dart';

// **************************************************************************
// RiverpodGenerator
// **************************************************************************

// GENERATED CODE - DO NOT MODIFY BY HAND
// ignore_for_file: type=lint, type=warning

@ProviderFor(PresetNotifier)
final presetProvider = PresetNotifierProvider._();

final class PresetNotifierProvider
    extends $NotifierProvider<PresetNotifier, PresetState> {
  PresetNotifierProvider._()
    : super(
        from: null,
        argument: null,
        retry: null,
        name: r'presetProvider',
        isAutoDispose: true,
        dependencies: null,
        $allTransitiveDependencies: null,
      );

  @override
  String debugGetCreateSourceHash() => _$presetNotifierHash();

  @$internal
  @override
  PresetNotifier create() => PresetNotifier();

  /// {@macro riverpod.override_with_value}
  Override overrideWithValue(PresetState value) {
    return $ProviderOverride(
      origin: this,
      providerOverride: $SyncValueProvider<PresetState>(value),
    );
  }
}

String _$presetNotifierHash() => r'13359e63d0a6b5da8d3c10e4f9211367bf95c1dc';

abstract class _$PresetNotifier extends $Notifier<PresetState> {
  PresetState build();
  @$mustCallSuper
  @override
  void runBuild() {
    final ref = this.ref as $Ref<PresetState, PresetState>;
    final element =
        ref.element
            as $ClassProviderElement<
              AnyNotifier<PresetState, PresetState>,
              PresetState,
              Object?,
              Object?
            >;
    element.handleCreate(ref, build);
  }
}
