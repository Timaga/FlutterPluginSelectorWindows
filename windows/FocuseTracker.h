#include <windows.h>
#include <iostream>
#include <UIAutomation.h>
#include <ole2.h>
#include <string>
#include <locale>
#include <codecvt>
#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>
class FocusTracker
{

public:
    IUIAutomation *g_pAutomation = NULL;
    FocusTracker();
    FocusTracker(flutter::PluginRegistrarWindows *registrar) noexcept;
    ~FocusTracker() noexcept;
    void HandleMethodCall(
        const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    // Прототипы функций
    void InitializeUIAutomation();
    void FinalizeUIAutomation();
    std::string WideStringToUtf8(const std::wstring &wstr);
    std::wstring StartTrackingFocus();
    std::wstring RemoveSpaces(const std::wstring &str);
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

protected:
    flutter::PluginRegistrarWindows *registrar_ = nullptr;
    std::unique_ptr<flutter::MethodChannel<>> channel_;
};