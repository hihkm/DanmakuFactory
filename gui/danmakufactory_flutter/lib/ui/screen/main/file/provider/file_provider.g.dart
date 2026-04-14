// GENERATED CODE - DO NOT MODIFY BY HAND

part of 'file_provider.dart';

// **************************************************************************
// RiverpodGenerator
// **************************************************************************

// GENERATED CODE - DO NOT MODIFY BY HAND
// ignore_for_file: type=lint, type=warning

@ProviderFor(FileNotifier)
final fileProvider = FileNotifierProvider._();

final class FileNotifierProvider
    extends $AsyncNotifierProvider<FileNotifier, FileState> {
  FileNotifierProvider._()
    : super(
        from: null,
        argument: null,
        retry: null,
        name: r'fileProvider',
        isAutoDispose: true,
        dependencies: null,
        $allTransitiveDependencies: null,
      );

  @override
  String debugGetCreateSourceHash() => _$fileNotifierHash();

  @$internal
  @override
  FileNotifier create() => FileNotifier();
}

String _$fileNotifierHash() => r'9468da5be750cf74630b1670a9b624b6b7af266c';

abstract class _$FileNotifier extends $AsyncNotifier<FileState> {
  FutureOr<FileState> build();
  @$mustCallSuper
  @override
  void runBuild() {
    final ref = this.ref as $Ref<AsyncValue<FileState>, FileState>;
    final element =
        ref.element
            as $ClassProviderElement<
              AnyNotifier<AsyncValue<FileState>, FileState>,
              AsyncValue<FileState>,
              Object?,
              Object?
            >;
    element.handleCreate(ref, build);
  }
}
