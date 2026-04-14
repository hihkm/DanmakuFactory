abstract class LocalStorage {
  //初始化
  Future<void> init();
  //打开
  Future<void> open();

  //保存数据
  void setValue<T>(String key, T value);

  //获取数据
  T getValue<T>(String key, {required T defaultValue});
}
