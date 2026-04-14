import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'provider/preset_provider.dart';
import 'widgets/build_danmaku_settings.dart';
import 'widgets/build_font_settings.dart';
import 'widgets/build_screen_settings.dart';

class PresetScreen extends ConsumerWidget {
  const PresetScreen({super.key});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    // 监听状态变化
    final uiState = ref.watch(presetProvider);
    // 获取 Notifier 发送动作
    final intent = ref.read(presetProvider.notifier);

    return Scaffold(
      appBar: AppBar(
        title: const Text('预设'),
        actionsPadding: const EdgeInsets.only(right: 15),
        actions: [
          IconButton(
            onPressed: () {
              intent.resetToDefault();
            },
            icon: const Row(
              mainAxisSize: MainAxisSize.min,
              children: [Icon(Icons.lock_reset), Text("重置")],
            ),
          ),
        ],
      ),
      body: SingleChildScrollView(
        child: Column(
          children: [
            buildFontSettings(context, uiState, intent),
            const SizedBox(height: 15),
            buildDanmakuSettings(context, uiState, intent),
            const SizedBox(height: 15),
            buildScreenSettings(context, uiState, intent),
          ],
        ),
      ),
    );
  }
}
