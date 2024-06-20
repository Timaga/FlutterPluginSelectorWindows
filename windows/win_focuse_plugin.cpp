#include "win_focuse_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>
#include "FocuseTracker.h"
#include <memory>
#include <sstream>

namespace win_focuse
{
  std::string WideStringToUtf8(const std::wstring &wstr);
  FocusTracker _focus_tracker = FocusTracker();
  // static
  void WinFocusePlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarWindows *registrar)
  {
    auto channel =
        std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
            registrar->messenger(), "win_focuse",
            &flutter::StandardMethodCodec::GetInstance());

    auto plugin = std::make_unique<WinFocusePlugin>();

    channel->SetMethodCallHandler(
        [plugin_pointer = plugin.get()](const auto &call, auto result)
        {
          plugin_pointer->HandleMethodCall(call, std::move(result));
        });

    registrar->AddPlugin(std::move(plugin));
  }

  WinFocusePlugin::WinFocusePlugin() {}

  WinFocusePlugin::~WinFocusePlugin() {}
  void WinFocusePlugin::HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result)
  {
    if (method_call.method_name().compare("StartTrackingFocus") == 0)
    {
      std::wstring trackedText = _focus_tracker.StartTrackingFocus();
      std::string utf8String = win_focuse::WideStringToUtf8(trackedText);
      result->Success(flutter::EncodableValue(utf8String));
    }
    else if (method_call.method_name().compare("InitializeUIAutomation") == 0)
    {
      _focus_tracker.InitializeUIAutomation();
    }
    else if (method_call.method_name().compare("FinalizeUIAutomation") == 0)
    {
      _focus_tracker.FinalizeUIAutomation();
    }
    else if (method_call.method_name().compare("CoUninitialize") == 0)
    {
      CoUninitialize();
    }
    else
    {
      result->NotImplemented();
    }
  }
  std::string WideStringToUtf8(const std::wstring &wstr)
  {
    if (wstr.empty())
      return std::string();
    int count = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, NULL, NULL);
    std::string str(count - 1, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
    return str;
  }

} // namespace win_focuse
