import 'package:riverpod_annotation/riverpod_annotation.dart';

import '../model/main_state.dart';

part 'main_provider.g.dart';

@riverpod
class MainNotifier extends _$MainNotifier {
  @override
  MainState build() => const MainState();
}
