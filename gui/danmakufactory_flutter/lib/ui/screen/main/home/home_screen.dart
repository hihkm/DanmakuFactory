import 'package:danmakufactory_flutter/ui/screen/main/home/provider/home_provider.dart';
import 'package:danmakufactory_flutter/utils/app_util.dart';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import 'model/home_state.dart';

const openSourceUrl = "https://github.com/hihkm/DanmakuFactory";

class HomeScreen extends ConsumerWidget {
  const HomeScreen({super.key});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    // 监听状态变化
    final uiState = ref.watch(homeProvider);
    // 获取 Notifier 发送动作
    final intent = ref.read(homeProvider.notifier);

    return Scaffold(
      appBar: AppBar(title: const Text("首页")),
      body: Stack(
        children: [
          Positioned(
            child: Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Expanded(
                  child: Column(
                    mainAxisSize: MainAxisSize.min,
                    children: [
                      const Text(
                        "软件由DanmakuFactory强力驱动",
                        style: TextStyle(fontSize: 18),
                      ),
                      const SizedBox(height: 8),
                      InkWell(
                        child: const Text(
                          "开源地址:${openSourceUrl}",
                        ),
                        onTap: () {
                          AppUtil.openUrl(openSourceUrl);
                        },
                      ),
                    ],
                  ),
                ),
              ],
            ),
          ),
          Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  const Text("输入文件(可多选)"),
                  Visibility(
                    visible: uiState.inputFiles.isNotEmpty,
                    child: Row(mainAxisSize: MainAxisSize.min,children: [
                      const SizedBox(width: 15),
                      Text("已选择:${uiState.inputFiles.length}")
                    ],),
                  ),
                ],
              ),
              const SizedBox(height: 8),
              ElevatedButton(
                onPressed: () {
                  intent.pickInputFiles();
                },
                child: const Text("选择文件"),
              ),
              const SizedBox(height: 15),
              Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  const Text("输出格式"),
                  const SizedBox(width: 15),
                  Container(
                    decoration: BoxDecoration(
                      border: Border.all(color: Colors.grey, width: 1),
                      borderRadius: BorderRadius.circular(8),
                    ),
                    child: DropdownButton<String>(
                      padding: EdgeInsetsGeometry.symmetric(horizontal: 8),
                      value: uiState.outputDanmakuFormat.value,
                      underline: const SizedBox(),
                      items: DanmakuFormat.values.map((DanmakuFormat format) {
                        return DropdownMenuItem<String>(
                          value: format.value,
                          child: Text(format.title),
                        );
                      }).toList(),
                      onChanged: (String? newValue) {
                        if (newValue == null) return;
                        intent.changeOutputDanmakuFormat(newValue);
                      },
                      borderRadius: BorderRadius.circular(8),
                      icon: const Icon(
                        Icons.arrow_drop_down,
                        color: Colors.grey,
                      ),
                    ),
                  ),
                ],
              ),
            ],
          ),
        ],
      ),
      floatingActionButton: FloatingActionButton.extended(
        onPressed: () {
          intent.convertDanmaku();
        },
        icon: const Icon(Icons.swap_horiz),
        label: const Text("转换"),
      ),
    );
  }
}
