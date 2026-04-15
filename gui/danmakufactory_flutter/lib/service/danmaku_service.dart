import 'package:path/path.dart' as p;
import 'package:tuple/tuple.dart';

import '../utils/toast_util.dart';
import 'cmd_service.dart';

class DanmakuService {
  // 转换弹幕
  convertDanmakuList(
    List<String> inputFiles,
    String outputDirPath,
    String outputFormatExt,
  ) {
    String otherArgs = CmdService.getConvertCmdConfig();

    //任务进度Toast
    ToastUtil.showProgressToast(
      itemList: inputFiles,
      processAction: (item) async {
        final outputFile = p.join(
          outputDirPath,
          "${p.basenameWithoutExtension(item)}.${outputFormatExt}",
        );

        print("输出文件:${outputFile}");

        //执行命令
        int runCmdResult = await CmdService.runCmdByUi(item, outputFile, otherArgs);
        print("执行结果: $runCmdResult");

        return Tuple2(runCmdResult == 0, runCmdResult);
      },
      onFinish: (errItemList) {
        if (errItemList.isEmpty){
          ToastUtil.success('处理成功');
          return;
        }

        final errNum = errItemList.length;
        final totalNum = inputFiles.length;
        ToastUtil.warning(
          '成功: ${totalNum - errNum}, 失败:${errNum}',
          milliseconds: 5000,
        );
      },
      onError: (err) {
        print(err);
        ToastUtil.error('处理失败: ${err}', milliseconds: 5000);
      },
    );
  }


}
