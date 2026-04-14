import 'dart:io';
import 'package:path_provider/path_provider.dart';
import 'package:path/path.dart' as p;
import 'package:file_picker/file_picker.dart';
import 'package:flutter/material.dart';
import 'dart:async';

import 'package:danmakufactory/danmakufactory.dart' as danmakufactory;

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  late String testHiStr;
  late int sumResult;
  late Future<int> sumAsyncResult;
  File? inputFile;
  Directory? appDocDir;

  @override
  void initState() {
    super.initState();
    sumResult = danmakufactory.sum(1, 2);
    testHiStr = danmakufactory.testHi();
    sumAsyncResult = danmakufactory.sumAsync(3, 4);
  }

  @override
  Widget build(BuildContext context) {
    const textStyle = TextStyle(fontSize: 25);
    const spacerSmall = SizedBox(height: 10);
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(title: const Text('Native Packages')),
        body: SingleChildScrollView(
          child: Container(
            alignment: Alignment.center,
            padding: const EdgeInsets.all(10),
            child: Column(
              children: [
                const Text(
                  'The native code',
                  style: textStyle,
                  textAlign: TextAlign.center,
                ),
                spacerSmall,
                Text(
                  'sum(1, 2) = $sumResult',
                  style: textStyle,
                  textAlign: TextAlign.center,
                ),
                spacerSmall,
                FutureBuilder<int>(
                  future: sumAsyncResult,
                  builder: (BuildContext context, AsyncSnapshot<int> value) {
                    final displayValue = (value.hasData)
                        ? value.data
                        : 'loading';
                    return Text(
                      'await sumAsync(3, 4) = $displayValue',
                      style: textStyle,
                      textAlign: TextAlign.center,
                    );
                  },
                ),
                spacerSmall,
                Text(
                  'testHi() = $testHiStr',
                  style: textStyle,
                  textAlign: TextAlign.center,
                ),
                spacerSmall,
                ElevatedButton(
                  onPressed: () async {
                    FilePickerResult? result = await FilePicker.platform
                        .pickFiles();

                    if (result != null) {
                      inputFile = File(result.files.single.path!);
                      print("输入文件:${inputFile?.path}");
                    } else {}

                    appDocDir = await getApplicationDocumentsDirectory();
                    print("appDocDir目录:${appDocDir?.path}");
                  },
                  child: const Text("选择文件"),
                ),
                spacerSmall,
                Builder(
                  builder: (context) {
                    return ElevatedButton(
                      onPressed: () {
                        final finalInputFile = inputFile;
                        if (finalInputFile == null) {
                          print("请选择文件");
                          return;
                        }
                        //判断是否有输出目录,没有就创建一个
                        final outputDir = Directory(
                          "${appDocDir?.path}/danmakufactoryOutput",
                        );

                        if (!outputDir.existsSync()) {
                          outputDir.createSync(recursive: true);
                        }

                        final finalOutputFile = p.join(
                          outputDir.path,
                          "${p.basenameWithoutExtension(finalInputFile.path)}.ass",
                        );

                        print("输出文件:${finalOutputFile}");

                        int runCmdResult = danmakufactory.runCmd(
                          "-i ${finalInputFile.path} -o ${finalOutputFile}",
                        );
                        print("执行结果: $runCmdResult");
                        ScaffoldMessenger.of(context).showSnackBar(
                          SnackBar(
                            content: Text("执行结果: $runCmdResult"),
                            duration: Duration(seconds: 2),
                          ),
                        );
                      },
                      child: const Text("执行"),
                    );
                  },
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
