import 'dart:io';

import 'package:path/path.dart' as p;

import 'package:share_plus/share_plus.dart';
import 'package:url_launcher/url_launcher.dart';

class AppUtil {
  AppUtil._();

  // 浏览器打开
  static Future<bool> openUrl(String url) async {
    final Uri uri = Uri.parse(url);
    try {
      if (await canLaunchUrl(uri)) {
        return await launchUrl(uri,mode: LaunchMode.externalApplication);
      }
    } catch (e) {
      print(e);
    }
    return false;
  }
}
