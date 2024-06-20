import 'package:plugin_platform_interface/plugin_platform_interface.dart';
import 'package:win_focuse/win_focuse_method_channel.dart';


abstract class WinFocusePlatform extends PlatformInterface {
  /// Constructs a WinPluginPlatform.
  WinFocusePlatform() : super(token: _token);

  static final Object _token = Object();

  static WinFocusePlatform _instance = MethodChannelWinFocuse();

  /// The default instance of [WinPluginPlatform] to use.
  ///
  /// Defaults to [MethodChannelWinPlugin].
  static WinFocusePlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [WinPluginPlatform] when
  /// they register themselves.
  static set instance(WinFocusePlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> StartTrackingFocus() {
    throw UnimplementedError('StartTrackingFocus() has not been implemented.');
  }

  void InitializeUIAutomation(){
    throw UnimplementedError('InitializeUIAutomation() has not been implemented.');
  }
   void FinalizeUIAutomation(){
    throw UnimplementedError('FinalizeUIAutomation() has not been implemented.');
  }
   void CoUninitialize(){
    throw UnimplementedError('CoUninitialize() has not been implemented.');
  }
}
