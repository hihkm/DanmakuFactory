import 'package:flutter/material.dart';

/// 带有标题的步进器
class TitleStepper extends StatefulWidget {
  const TitleStepper({
    required this.stepOnChanged,
    this.title,
    this.value = 0,
    this.minVal = 0,
    this.maxVal = double.maxFinite,
    this.steps = 1,
    super.key,
  });

  final String? title;
  final ValueChanged<num> stepOnChanged;
  final num value;
  final num minVal;
  final num maxVal;
  final num steps;

  @override
  State<TitleStepper> createState() => _TitleStepperState();
}

class _TitleStepperState extends State<TitleStepper> {
  late TextEditingController _controller;
  late FocusNode _focusNode;

  @override
  void initState() {
    super.initState();
    _controller = TextEditingController(text: _formatValue(widget.value));
    _focusNode = FocusNode();
    _focusNode.addListener(_onFocusChange);
  }

  @override
  void didUpdateWidget(TitleStepper oldWidget) {
    super.didUpdateWidget(oldWidget);
    if (oldWidget.value != widget.value) {
      _controller.text = _formatValue(widget.value);
    }
  }

  @override
  void dispose() {
    _focusNode.removeListener(_onFocusChange);
    _focusNode.dispose();
    _controller.dispose();
    super.dispose();
  }

  void _onFocusChange() {
    if (!_focusNode.hasFocus) {
      _inputValue();
    }
  }

  String _formatValue(num value) {
    final decimalPart = widget.steps.toString().split('.');
    final decimals = decimalPart.length > 1 ? decimalPart[1].length : 0;
    return value.toStringAsFixed(decimals > 0 ? decimals : 0);
  }

  void _increment() {
    final currentValue =
        double.tryParse(_controller.text) ?? widget.value.toDouble();
    final newValue = (currentValue + widget.steps.toDouble()).clamp(
      widget.minVal.toDouble(),
      widget.maxVal.toDouble(),
    );
    _controller.text = _formatValue(newValue);
    widget.stepOnChanged(newValue);
  }

  void _decrement() {
    final currentValue =
        double.tryParse(_controller.text) ?? widget.value.toDouble();
    final newValue = (currentValue - widget.steps.toDouble()).clamp(
      widget.minVal.toDouble(),
      widget.maxVal.toDouble(),
    );
    _controller.text = _formatValue(newValue);
    widget.stepOnChanged(newValue);
  }

  void _inputValue({String? value}) {
    value = value ?? _controller.text;
    final newValue = double.tryParse(value);
    if (newValue == null) {
      _controller.text = _formatValue(widget.value);
      return;
    }

    final finalValue = newValue.clamp(
      widget.minVal.toDouble(),
      widget.maxVal.toDouble(),
    );
    _controller.text = _formatValue(finalValue);
    widget.stepOnChanged(finalValue);
  }

  @override
  Widget build(BuildContext context) {
    return Row(
      mainAxisSize: MainAxisSize.min,
      children: [
        Visibility(
          visible: widget.title != null,
          child: Row(
            children: [Text(widget.title ?? ""), const SizedBox(width: 8)],
          ),
        ),

        Container(
          decoration: BoxDecoration(
            color: Theme.of(context).colorScheme.primaryContainer,
            borderRadius: BorderRadius.circular(99),
          ),
          child: Row(
            mainAxisSize: MainAxisSize.min,
            crossAxisAlignment: CrossAxisAlignment.center,
            children: [
              InkWell(
                onTap: _decrement,
                borderRadius: BorderRadius.circular(99),
                child: const Padding(
                  padding: EdgeInsets.all(4.0),
                  child: Icon(Icons.remove, size: 22),
                ),
              ),

              SizedBox(
                width: 50,
                child: TextField(
                  controller: _controller,
                  focusNode: _focusNode,
                  onSubmitted: (value) {
                    _inputValue(value: value);
                  },
                  textAlign: TextAlign.center,
                  decoration: const InputDecoration(
                    border: InputBorder.none,
                    contentPadding: EdgeInsets.all(1),
                    isDense: true,
                  ),
                ),
              ),

              InkWell(
                onTap: _increment,
                borderRadius: BorderRadius.circular(99),
                child: const Padding(
                  padding: EdgeInsets.all(4.0),
                  child: Icon(Icons.add, size: 22),
                ),
              ),
            ],
          ),
        ),
      ],
    );
  }
}
