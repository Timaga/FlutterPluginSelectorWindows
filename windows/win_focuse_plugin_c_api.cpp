#include "include/win_focuse/win_focuse_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "win_focuse_plugin.h"
#include "FocuseTracker.h"

void WinFocusePluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  win_focuse::WinFocusePlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
class FocuseTrackerPlugin : public flutter::Plugin
{
public:
    static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

    FocuseTrackerPlugin(flutter::PluginRegistrarWindows *registrar);

    virtual ~FocuseTrackerPlugin();

protected:
    // The registrar for this plugin.
    flutter::PluginRegistrarWindows *registrar_ = nullptr;

    std::unique_ptr<FocusTracker> focuse_tracker_;
};

FocuseTrackerPlugin::FocuseTrackerPlugin(flutter::PluginRegistrarWindows *registrar)
    : registrar_(registrar)
{

    focuse_tracker_ = std::make_unique<FocusTracker>(registrar_);
}

FocuseTrackerPlugin::~FocuseTrackerPlugin() {}

// static
void FocuseTrackerPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar)
{
    auto plugin = std::make_unique<FocuseTrackerPlugin>(registrar);
    registrar->AddPlugin(std::move(plugin));
}