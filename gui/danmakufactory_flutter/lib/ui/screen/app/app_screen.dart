import 'package:flutter/material.dart';
import 'package:toastification/toastification.dart';

import 'route/app_routes.dart';

class AppScreen extends StatelessWidget {
  const AppScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return ToastificationWrapper(
      child: MaterialApp.router(
        debugShowCheckedModeBanner: false,
        routerConfig: appRouterConfig,
      ),
    );
  }
}