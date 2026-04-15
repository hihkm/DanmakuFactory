import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
/// Provider日志
final class ProviderLogger extends ProviderObserver {
  @override
  void didUpdateProvider(
    ProviderObserverContext context,
    Object? previousValue,
    Object? newValue,
  ) {
    debugPrint('''
{
  "provider": "${context.provider}",
  "newValue": "$newValue",
  "mutation": "${context.mutation}"
}''');
  }
}
