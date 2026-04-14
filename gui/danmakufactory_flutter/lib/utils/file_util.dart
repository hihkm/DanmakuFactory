
import 'dart:io';
import 'package:share_plus/share_plus.dart';
import 'package:url_launcher/url_launcher.dart';

import 'platform_util.dart';

class FileUtil {
  FileUtil._();

  /// 分享文件
  static Future<bool> shareFiles(List<File> files) async {
    try {
      if (files.isEmpty) return false;

      // 检查文件是否存在
      for (var file in files) {
        if (!await file.exists()) {
          return false;
        }
      }

      await Share.shareXFiles(files.map((file) => XFile(file.path)).toList());
      return true;
    } catch (e) {
      print('分享失败：$e');
      return false;
    }
  }

  //删除文件
  static Future<bool> deleteFiles(List<File> files) async {
    try {
      if (files.isEmpty) return false;

      // 检查文件是否存在
      for (var file in files) {
        if (!await file.exists()) {
          return false;
        }
      }

      for (var file in files) {
        await file.delete();
      }
      return true;
    } catch (e) {
      print('删除失败：$e');
      return false;
    }
  }

  ///打开文件夹
  ///移动端都是存储在app私有文件夹中,无法打开
  static Future<bool> openFolder(String path) async {
    return await runPlatformGroupAsync<bool>(
      onDesktop: () async {
        final Uri uri = Uri.directory(path);
        if (await canLaunchUrl(uri)) {
          return await launchUrl(uri);
        } else {
          return false;
        }
      },
      orElse: () async {
        return false;
      },
    );
  }

}