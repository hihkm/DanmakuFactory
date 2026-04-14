import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'main_logic.dart';
import 'provider/main_provider.dart';

class MainScreen extends ConsumerWidget {
  const MainScreen({super.key, required this.logic});

  final MainLogic logic;

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final provider = ref.watch(mainProvider);

    final isDesktop = _isDesktop(context);

    if (isDesktop) {
      return _buildDesktopLayout(context);
    } else {
      return _buildMobileLayout(context);
    }
  }

  bool _isDesktop(BuildContext context) {
    final width = MediaQuery.of(context).size.width;
    return width >= 600;
  }

  Widget _buildMobileLayout(BuildContext context) {
    return Scaffold(
      body: logic.navigationShell,
      bottomNavigationBar: BottomNavigationBar(
        currentIndex: logic.navigationShell.currentIndex,
        onTap: logic.changeIndex,
        items: const [
          BottomNavigationBarItem(icon: Icon(Icons.home), label: '首页'),
          BottomNavigationBarItem(icon: Icon(Icons.file_open), label: '文件'),
          BottomNavigationBarItem(
            icon: Icon(Icons.phonelink_setup),
            label: '预设',
          ),
        ],
      ),
    );
  }


  Widget _buildDesktopLayout(BuildContext context) {
    final isDark = Theme.of(context).brightness == Brightness.dark;

    return Scaffold(
      body: Row(
        children: [
          Container(
            width: 80,
            decoration: BoxDecoration(
              color: Theme.of(context).colorScheme.surface,
              border: Border(
                right: BorderSide(
                  color: isDark
                      ? Colors.white.withOpacity(0.1)
                      : Colors.black.withOpacity(0.1),
                  width: 1,
                ),
              ),
            ),
            child: NavigationRail(
              selectedIndex: logic.navigationShell.currentIndex,
              onDestinationSelected: logic.changeIndex,
              labelType: NavigationRailLabelType.all,
              backgroundColor: Colors.transparent,
              minWidth: 80,
              destinations: const [
                NavigationRailDestination(
                  icon: Icon(Icons.home),
                  label: Text('首页'),
                ),
                NavigationRailDestination(
                  icon: Icon(Icons.file_open),
                  label: Text('文件'),
                ),
                NavigationRailDestination(
                  icon: Icon(Icons.phonelink_setup),
                  label: Text('预设'),
                ),
              ],
            ),
          ),
          Expanded(
            child: logic.navigationShell,
          ),
        ],
      ),
    );
  }
}
