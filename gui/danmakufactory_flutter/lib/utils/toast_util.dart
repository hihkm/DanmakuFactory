import 'package:flutter/material.dart';
import 'package:toastification/toastification.dart';
import 'package:tuple/tuple.dart';

class ToastUtil {
  ToastUtil._();

  //默认时间
  static const int defaultMilliseconds = 1500;

  static void success(String msg, {int milliseconds = defaultMilliseconds}) {
    show(msg, type: ToastificationType.success, milliseconds: milliseconds);
  }

  static void error(String msg, {int milliseconds = defaultMilliseconds}) {
    show(msg, type: ToastificationType.error, milliseconds: milliseconds);
  }

  static void info(String msg, {int milliseconds = defaultMilliseconds}) {
    show(msg, type: ToastificationType.info, milliseconds: milliseconds);
  }

  static void warning(String msg, {int milliseconds = defaultMilliseconds}) {
    show(msg, type: ToastificationType.warning, milliseconds: milliseconds);
  }

  static void showAlways(String msg) {
    show(msg, type: ToastificationType.info, milliseconds: null);
  }

  static void show(
    String msg, {
    int? milliseconds = defaultMilliseconds,
    ToastificationType? type,
    AlignmentGeometry? alignment = Alignment.center,
  }) {
    toastification.show(
      title: Text(msg),
      autoCloseDuration: milliseconds == null ? null : Duration(milliseconds: milliseconds),
      type: type,
      alignment: alignment,
    );
  }

  //显示进度toast
  static Future<void> showProgressToast<T, R>({
    required List<T> itemList,
    //处理行为:需返回:判断结果和实际结果
    required Future<Tuple2<bool, R>> Function(T item) processAction,
    //完成回调
    required void Function(List<Tuple2<T, R>> errItemList) onFinish,
    //错误回调
    void Function(Exception e)? onError,
  }) async {
    final int totalCount = itemList.length;

    // 1. 创建一个进度监听器
    final ValueNotifier<_ToastProgressBean> progressNotifier = ValueNotifier(
      _ToastProgressBean(0, totalCount),
    );

    // 2. 显示持久化的 Toast
    final toastItem = toastification.show(
      type: ToastificationType.info,
      style: ToastificationStyle.flatColored,
      title: const Text('正在处理...'),
      // 取消自动关闭，让它一直显示，直到我们手动关闭
      autoCloseDuration: null,
      // 隐藏它自带的时间倒计时进度条
      showProgressBar: false,
      callbacks: ToastificationCallbacks(
        onDismissed: (toastItem) {
          // 在 Toast 完全从屏幕和组件树中移除后，再安全地销毁 Notifier
          progressNotifier.dispose();
        },
      ),
      // 核心：在 description 中嵌入一个支持局部刷新的进度条
      description: ValueListenableBuilder<_ToastProgressBean>(
        valueListenable: progressNotifier,
        builder: (context, state, child) {
          return Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            mainAxisSize: MainAxisSize.min,
            children: [
              // 显示文字进度
              Text('进度: ${state.current} / ${state.total}'),
              const SizedBox(height: 8),
              // 显示线性进度条
              LinearProgressIndicator(
                value: state.progress,
                backgroundColor: Colors.grey[300],
                color: Colors.blue,
              ),
            ],
          );
        },
      ),
    );

    // 错误信息列表
    List<Tuple2<T, R>> errItemList = [];

    try {
      for (int i = 0; i < totalCount; i++) {
        final item = itemList[i];
        progressNotifier.value = _ToastProgressBean(i, totalCount);

        final resultPair = await processAction(item);

        if (!resultPair.item1) {
          errItemList.add(Tuple2(item, resultPair.item2));
        }

        progressNotifier.value = _ToastProgressBean(i + 1, totalCount);
      }

      // 4. 处理完成：关闭进度 Toast
      toastification.dismiss(toastItem);
      onFinish(errItemList);
    } on Exception catch (e) {
      toastification.dismiss(toastItem);
      onError?.call(e);
    }
  }
}

class _ToastProgressBean {
  final int current; // 当前处理到第几个
  final int total; // 总数

  _ToastProgressBean(this.current, this.total);

  // 计算百分比进度 (0.0 ~ 1.0)
  double get progress => total == 0 ? 0 : current / total;
}
