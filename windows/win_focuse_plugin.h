#ifndef FLUTTER_PLUGIN_WIN_FOCUSE_PLUGIN_H_
#define FLUTTER_PLUGIN_WIN_FOCUSE_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace win_focuse {

class WinFocusePlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  WinFocusePlugin();

  virtual ~WinFocusePlugin();

  // Disallow copy and assign.
  WinFocusePlugin(const WinFocusePlugin&) = delete;
  WinFocusePlugin& operator=(const WinFocusePlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace win_focuse

#endif  // FLUTTER_PLUGIN_WIN_FOCUSE_PLUGIN_H_
