import 'package:flutter/material.dart';

import '../model/preset_state.dart';
import '../provider/preset_provider.dart';
import 'title_stepper.dart';

///构建画面设置
Widget buildScreenSettings(
    BuildContext context,
    PresetState uiState,
    PresetNotifier intent,
    ) {
  return Column(
    children: [
      ListTile(title: const Text("画面设置")),
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
              title: "滚动弹幕显示区域",
              stepOnChanged: (val) {
                intent.changeDanmakuScrollArea(val.toDouble());
              },
              value: uiState.danmakuScrollArea,
              minVal: 0.1,
              maxVal: 1.0,
              steps: 0.1,
            ),
            TitleStepper(
              title: "全部弹幕显示区域",
              stepOnChanged: (val) {
                intent.changeDanmakuAllArea(val.toDouble());
              },
              value: uiState.danmakuAllArea,
              minVal: 0.1,
              maxVal: 1.0,
              steps: 0.1,
            ),

            const Text("分辨率"),

            Row(
              spacing: 5,
              mainAxisSize: MainAxisSize.min,
              children: [
                TitleStepper(
                  stepOnChanged: (val) {
                    intent.changeResolutionWidth(val.toInt());
                  },
                  value: uiState.resolutionWidth,
                  minVal: 1,
                  steps: 1,
                ),
                const Icon(Icons.close),
                TitleStepper(
                  stepOnChanged: (val) {
                    intent.changeResolutionHeight(val.toInt());
                  },
                  value: uiState.resolutionHeight,
                  minVal: 1,
                  steps: 1,
                ),
              ],
            ),
          ],
        ),
      ),
    ],
  );
}