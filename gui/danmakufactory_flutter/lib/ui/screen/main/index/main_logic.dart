
import 'package:file_picker/file_picker.dart';
import 'package:go_router/go_router.dart';

class MainLogic {
  final StatefulNavigationShell navigationShell;

  MainLogic({required this.navigationShell});

  Future<void> changeIndex(int index) async {
    navigationShell.goBranch(
      index,
      initialLocation: index == navigationShell.currentIndex,
    );
  }
}
