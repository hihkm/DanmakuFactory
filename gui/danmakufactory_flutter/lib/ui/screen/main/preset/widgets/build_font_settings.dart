import 'package:flutter/material.dart';

import '../model/preset_state.dart';
import '../provider/preset_provider.dart';
import 'title_stepper.dart';

/// 构建文字设置
Widget buildFontSettings(
  BuildContext context,
  PresetState uiState,
  PresetNotifier intent,
) {
  return Column(
    children: [
      ListTile(title: const Text("文字设置")),
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
              title: "字体大小",
              stepOnChanged: (val) {
                intent.changeTextSize(val.toInt());
              },
              value: uiState.textSize,
              minVal: 1,
            ),
            TitleStepper(
              title: "阴影",
              stepOnChanged: (val) {
                intent.changeTextShadow(val.toInt());
              },
              value: uiState.textShadow,
              minVal: 1,
              maxVal: 4,
            ),

            TitleStepper(
              title: "不透明度",
              stepOnChanged: (val) {
                intent.changeTextOpacity(val.toInt());
              },
              value: uiState.textOpacity,
              minVal: 1,
              maxVal: 255,
            ),
            TitleStepper(
              title: "描边",
              stepOnChanged: (val) {
                intent.changeTextOutline(val.toInt());
              },
              value: uiState.textOutline,
              minVal: 0,
              maxVal: 4,
            ),
            Row(
              mainAxisSize: MainAxisSize.min,
              children: [
                Checkbox(
                  value: uiState.isBold,
                  onChanged: (val) {
                    intent.changeIsBold(val ?? false);
                  },
                ),
                const Text("粗体"),
              ],
            ),
          ],
        ),
      ),
    ],
  );
}
