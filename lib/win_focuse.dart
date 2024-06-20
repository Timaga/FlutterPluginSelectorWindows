// You have generated a new plugin project without specifying the `--platforms`
// flag. A plugin project with no platform support was generated. To add a
// platform, run `flutter create -t plugin --platforms <platforms> .` under the
// same directory. You can also find a detailed instruction on how to add
// platforms in the `pubspec.yaml` at
// https://flutter.dev/docs/development/packages-and-plugins/developing-packages#plugin-platforms.



import 'package:win_focuse/win_focuse_platform_interface.dart';

class WinFocuse {
  Future<String?> StartTrackingFocus() {
    return WinFocusePlatform.instance.StartTrackingFocus();
  }


  void InitializeUIAutomation() {
    return WinFocusePlatform.instance.InitializeUIAutomation();
  }

  void FinalizeUIAutomation() {
    return WinFocusePlatform.instance.FinalizeUIAutomation();
  }

  void CoUninitialize() {
    return WinFocusePlatform.instance.CoUninitialize();
  }
}
