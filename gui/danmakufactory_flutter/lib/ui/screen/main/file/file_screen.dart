import 'dart:ui';

import 'package:danmakufactory_flutter/ui/screen/main/file/provider/sync_file_provider.dart';
import 'package:danmakufactory_flutter/utils/platform_util.dart';
import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:go_router/go_router.dart';

import 'provider/file_provider.dart';
import 'package:path/path.dart' as p;

class FileScreen extends ConsumerWidget {
  FileScreen({super.key});

  final GlobalKey<RefreshIndicatorState> _refreshKey = GlobalKey<RefreshIndicatorState>();

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    // 监听状态变化
    final uiState = ref.watch(fileProvider);
    final intent = ref.read(fileProvider.notifier);
    final syncUiState = ref.watch(syncFileProvider);
    final syncIntent = ref.read(syncFileProvider.notifier);


    return PopScope(
      canPop: !syncUiState.isManageModel,
      onPopInvokedWithResult: (didPop, result) async {
        if (didPop) {
          context.pop();
          return;
        }
        final bool isManageModel = syncUiState.isManageModel;
        if (isManageModel) {
          syncIntent.toggleManageModel();
          return;
        }
      },
      child: Scaffold(
        appBar: AppBar(
          title: const Text('文件'),
          actionsPadding: const EdgeInsets.only(right: 15),
          actions: [
            Visibility(
              visible: syncUiState.isManageModel,
              child: Row(
                mainAxisSize: MainAxisSize.min,
                children: [
                  uiState.when(
                    data: (fileState) {
                      final bool status = intent.isAllChecked();
                      return Checkbox(
                        value: status,
                        onChanged: (value) {
                          intent.toggleAllCheckStatus();
                        },
                      );
                    },
                    error: (err, stack) => const SizedBox(),
                    loading: () => const SizedBox(),
                  ),

                  IconButton(
                    onPressed: () {
                      intent.shareFiles();
                    },
                    icon: Icon(Icons.share),
                  ),
                  IconButton(
                    onPressed: () {
                      intent.deleteFiles();
                    },
                    icon: Icon(Icons.delete),
                  ),
                ],
              ),
            ),

            IconButton(
              onPressed: () {
                bool afterStatus = syncIntent.toggleManageModel();
                if (!afterStatus) {
                  intent.changeAllCheckStatus(false);
                }
              },
              icon: Icon(
                Icons.rule,
                color: syncUiState.isManageModel ? Colors.red : Colors.grey,
              ),
            ),

            IconButton(
              onPressed: () {
                _refreshKey.currentState?.show();
              },
              icon: Icon(Icons.refresh),
            ),

            runPlatformGroup(
              onDesktop: () {
                return IconButton(
                  onPressed: () {
                    intent.openOutputDir();
                  },
                  icon: Icon(Icons.folder),
                );
              },
              orElse: () {
                return const SizedBox();
              },
            ),
          ],
        ),
        body: uiState.when(
          data: (fileState) {
            return RefreshIndicator(
              key: _refreshKey,
              onRefresh: () async => {await intent.refreshList()},
              child: ListView.builder(
                padding: const EdgeInsets.symmetric(horizontal: 10),
                itemCount: fileState.outputFileItems.length,
                itemBuilder: (BuildContext context, int index) {
                  final item = fileState.outputFileItems[index];
                  final file = item.file;
                  return Container(
                    margin: const EdgeInsets.symmetric(vertical: 5),
                    child: ListTile(
                      title: Text(p.basename(file.path)),
                      subtitle: SelectableText(
                        file.path,
                        style: const TextStyle(fontSize: 10),
                      ),
                      leading: const Icon(Icons.insert_drive_file),
                      shape: RoundedRectangleBorder(
                        side: const BorderSide(color: Colors.grey),
                        borderRadius: BorderRadius.circular(6),
                      ),
                      trailing: syncUiState.isManageModel
                          ? Checkbox(
                              value: item.checked,
                              onChanged: (value) {
                                intent.checkOutputFileItem(item);
                              },
                            )
                          : null,
                      onLongPress: () {
                        bool afterStatus = syncIntent.toggleManageModel();
                        if (!afterStatus) {
                          intent.changeAllCheckStatus(false);
                        }
                      },
                      onTap: () {
                        if (syncUiState.isManageModel) {
                          intent.checkOutputFileItem(item);
                          return;
                        }
                      },
                    ),
                  );
                },
              ),
            );
          },
          error: (err, stack) => Center(child: Text('出错了: $err')),
          loading: () => const Center(child: CircularProgressIndicator()),
        ),
      ),
    );
  }
}
