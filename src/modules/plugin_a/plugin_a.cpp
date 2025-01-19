#include <windows.h>
#include <iostream>
#include "plugin_a.h"

class PluginA : public PluginInterface {
public:
    std::string execute() override {
        return "Plugin A executed";
    }
};

extern "C" __declspec(dllexport) PluginInterface* create_plugin() {
    return new PluginA();
}

extern "C" __declspec(dllexport) void destroy_plugin(PluginInterface* plugin) {
    delete plugin;
}

extern "C" BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}
