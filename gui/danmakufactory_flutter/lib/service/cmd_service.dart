import '../repository/settings_repository.dart';
import 'package:danmakufactory/danmakufactory.dart' as danmakufactory;

class CmdService {
  static const String _cmdFlagArguments = "-cmd";

  //是否是命令行模式
  static bool isCmdMode(List<String> args) {
    return args.contains(_cmdFlagArguments);
  }

  //命令行模式下运行命令
  static Future<int> runCmd(List<String> args) async {
    print('danmakufactory cmd args: $args');
    //移除cmd Flag
    args.remove(_cmdFlagArguments);
    //构建命令
    String cmd = args.join(" ");
    print("final cmd:${cmd}");
    //执行命令
    int runCmdResult = await danmakufactory.runCmdAsync(cmd);
    print("runCmdResult:${runCmdResult}");
    return runCmdResult;
  }

  // ui模式下运行命令
  static Future<int> runCmdByUi(
    String inputFile,
    String outputFile,
    String otherArgs,
  ) async {
    final cmd = "-i ${inputFile} -o ${outputFile} ${otherArgs}";
    //执行命令
    int runCmdResult = await danmakufactory.runCmdAsync(cmd);
    return runCmdResult;
  }

  //获取转换的命令行配置
  static String getConvertCmdConfig() {
    final textSize = SettingsRepository.loadTextSize();
    final textShadow = SettingsRepository.loadTextShadow();
    final textOpacity = SettingsRepository.loadTextOpacity();
    final textOutline = SettingsRepository.loadTextOutline();
    final isBold = SettingsRepository.loadIsBold();
    final danmakuScrollTime = SettingsRepository.loadDanmakuScrollTime();
    final danmakuFixedTime = SettingsRepository.loadDanmakuFixedTime();
    final danmakuDensity = SettingsRepository.loadDanmakuDensity();
    final List<String> danmakuBlockModeList =
        SettingsRepository.loadDanmakuBlockModeList();
    final danmakuScrollArea = SettingsRepository.loadDanmakuScrollArea();
    final danmakuAllArea = SettingsRepository.loadDanmakuAllArea();
    final resolutionWidth = SettingsRepository.loadResolutionWidth();
    final resolutionHeight = SettingsRepository.loadResolutionHeight();

    final args = <String>[
      "--force",
      "--fontsize",
      textSize.toString(),
      "--shadow",
      textShadow.toString(),
      "--opacity",
      textOpacity.toString(),
      "--outline",
      textOutline.toString(),
      "--bold",
      isBold.toString(),
      "--scrolltime",
      danmakuScrollTime.toString(),
      "--fixtime",
      danmakuFixedTime.toString(),
      "--density",
      danmakuDensity.toString(),
      "--scrollarea",
      danmakuScrollArea.toString(),
      "--displayarea",
      danmakuAllArea.toString(),
      "--resolution",
      "${resolutionWidth}x$resolutionHeight",
      if (danmakuBlockModeList.isNotEmpty) "--blockmode",
      danmakuBlockModeList.join("-"),
    ];

    return args.join(" ");
  }
}
