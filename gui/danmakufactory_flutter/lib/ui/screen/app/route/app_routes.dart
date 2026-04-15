import 'package:go_router/go_router.dart';

import '../../main/file/file_screen.dart';
import '../../main/home/home_screen.dart';
import '../../main/index/main_logic.dart';
import '../../main/index/main_screen.dart';
import '../../main/preset/preset_screen.dart';

class AppRouter {
  static const String initRoute = home;
  static const String home = '/Main/Home';
  static const String file = '/Main/File';
  static const String preset = '/Main/Preset';
}

final appRouterConfig = GoRouter(
  initialLocation: AppRouter.initRoute,
  debugLogDiagnostics: true,
  routes: [
    /// 主页
    StatefulShellRoute.indexedStack(
      builder: (context, state, navigationShell) {
        final logic = MainLogic(navigationShell: navigationShell);
        return MainScreen(logic: logic);
      },
      branches: [
        /// 首页
        StatefulShellBranch(
          routes: [
            GoRoute(
              path: AppRouter.home,
              builder: (context, state) => HomeScreen(),
            ),
          ],
        ),

        /// 文件
        StatefulShellBranch(
          routes: [
            GoRoute(
              path: AppRouter.file,
              builder: (context, state) => FileScreen(),
            ),
          ],
        ),

        /// 预设
        StatefulShellBranch(
          routes: [
            GoRoute(
              path: AppRouter.preset,
              builder: (context, state) => PresetScreen(),
            ),
          ],
        ),
      ],
    ),
  ],
);
