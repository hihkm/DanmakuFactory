import 'package:flutter/material.dart';

import '../model/preset_state.dart';
import '../provider/preset_provider.dart';
import 'title_stepper.dart';

///构建弹幕设置
Widget buildDanmakuSettings(
    BuildContext context,
    PresetState uiState,
    PresetNotifier intent,
    ) {
  return Column(
    children: [
      ListTile(title: const Text("弹幕设置")),
      Container(
        padding: EdgeInsets.all(8),
        decoration: BoxDecoration(
          border: Border.all(color: Colors.grey),
          borderRadius: BorderRadius.circular(8),
        ),
        child: Wrap(
          spacing: 10,
          runSpacing: 5,
          crossAxisAlignment: WrapCrossAlignment.center,
          children: [
            TitleStepper(
              title: "滚动弹幕通过时间",
              stepOnChanged: (val) {
                intent.changeDanmakuScrollTime(val.toDouble());
              },
              value: uiState.danmakuScrollTime,
              minVal: 0.1,
              steps: 0.1,
            ),
            TitleStepper(
              title: "固定弹幕停留时间",
              stepOnChanged: (val) {
                intent.changeDanmakuFixedTime(val.toDouble());
              },
              value: uiState.danmakuFixedTime,
              minVal: 0.1,
              steps: 0.1,
            ),

            Row(
              mainAxisSize: MainAxisSize.min,
              children: [
                TitleStepper(
                  title: "弹幕密度",
                  stepOnChanged: (val) {
                    intent.changeDanmakuDensity(val.toInt());
                  },
                  value: uiState.danmakuDensity,
                  minVal: -1,
                  steps: 1,
                ),

                SizedBox(width: 10),

                InkWell(
                  child: const Text(
                    "说明",
                    style: TextStyle(
                      color: Colors.red,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                  onTap: () {intent.showDanmakuDensityTip();},
                ),
              ],
            ),

            Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                const Text("按类型屏蔽"),
                Wrap(
                  children: DanmakuBlockMode.values.map((item) {
                    return Row(
                      mainAxisSize: MainAxisSize.min,
                      children: [
                        Checkbox(
                          value: intent.isDanmakuBlockMode(item),
                          onChanged: (val) {
                            intent.checkDanmakuBlockMode(item, val ?? false);
                          },
                        ),
                        Text(item.title),
                      ],
                    );
                  }).toList(),
                ),
              ],
            ),
          ],
        ),
      ),
    ],
  );
}