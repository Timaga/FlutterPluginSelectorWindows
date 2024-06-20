import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:win_focuse/win_focuse_platform_interface.dart';



/// An implementation of [WinPluginPlatform] that uses method channels.
class MethodChannelWinFocuse extends WinFocusePlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('win_focuse');

  @override
  Future<String?> StartTrackingFocus() async {
    final version =
        await methodChannel.invokeMethod<String>('StartTrackingFocus');
    return version;
  }

  @override
  void InitializeUIAutomation() async {
    await methodChannel.invokeMethod<String>('InitializeUIAutomation');
  }
   @override
  void FinalizeUIAutomation() async {
    await methodChannel.invokeMethod<String>('FinalizeUIAutomation');
  }
   @override
  void CoUninitialize() async {
    await methodChannel.invokeMethod<String>('CoUninitialize');
  }


}
