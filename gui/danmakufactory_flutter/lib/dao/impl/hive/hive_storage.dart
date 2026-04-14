import 'package:danmakufactory_flutter/dao/impl/hive/customize_hive_ext.dart';
import 'package:danmakufactory_flutter/dao/local_storage.dart';
import 'package:hive_ce_flutter/hive_ce_flutter.dart';


class HiveStorage extends LocalStorage {
  HiveStorage(this.storageName);

  static bool _isInit = false;
  final String storageName;
  late Box _box;

  @override
  Future<void> init() async {
    if (_isInit) {
      return;
    }
    _isInit = true;
    await Hive.initHive();
  }

  @override
  Future<void> open() async {
    _box = await Hive.openBox(storageName);
  }

  @override
  T getValue<T>(String key, {required T defaultValue}) {
    return _box.get(key, defaultValue: defaultValue) as T;
  }

  @override
  void setValue<T>(String key, T value) {
    _box.put(key, value);
  }
}
