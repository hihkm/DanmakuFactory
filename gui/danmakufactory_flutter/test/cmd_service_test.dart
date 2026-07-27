import 'package:danmakufactory_flutter/service/cmd_service.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  test('adds font-size-strict for ass to ass', () {
    final cmd = CmdService.buildCmdByUi(
      '/tmp/input.ass',
      '/tmp/output.ass',
      '--fontsize 30',
    );

    expect(cmd, contains('--font-size-strict'));
  });

  test('does not add font-size-strict for xml to ass', () {
    final cmd = CmdService.buildCmdByUi(
      '/tmp/input.xml',
      '/tmp/output.ass',
      '--fontsize 30',
    );

    expect(cmd, isNot(contains('--font-size-strict')));
  });
}
