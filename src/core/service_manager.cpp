#include "service_manager.h"
#include <iostream>
#include <windows.h>
#include <memory> // For std::shared_ptr

ServiceManager::~ServiceManager() {
    // When destroying the ServiceManager, unload all plugins.
    for (auto& plugin : plugins) {
        unloadPlugin(plugin.first);
    }
}

bool ServiceManager::loadPlugin(const std::string& pluginName, const std::string& path) {
    // Load the plugin DLL dynamically (Windows equivalent of dlopen)
    HMODULE handle = LoadLibrary(path.c_str());
    if (!handle) {
        std::cerr << "Error loading plugin " << pluginName << ": " << GetLastError() << std::endl;
        return false;
    }

    // Get the plugin factory function (Windows equivalent of dlsym)
    auto createPlugin = (PluginInterface* (*)()) GetProcAddress(handle, "create_plugin");
    if (!createPlugin) {
        std::cerr << "Error finding 'create_plugin' function in " << pluginName << ": " << GetLastError() << std::endl;
        FreeLibrary(handle);  // Close the DLL if the function is not found
        return false;
    }

    // Create the plugin instance
    std::shared_ptr<PluginInterface> plugin(createPlugin(), [handle](PluginInterface*) { FreeLibrary(handle); });
    plugins[pluginName] = plugin;
    return true;
}

void ServiceManager::unloadPlugin(const std::string& pluginName) {
    auto it = plugins.find(pluginName);
    if (it != plugins.end()) {
        plugins.erase(it);
    }
}

std::string ServiceManager::executePlugin(const std::string& pluginName) {
    auto it = plugins.find(pluginName);
    if (it != plugins.end()) {
        return it->second->execute();
    } else {
        return "Plugin not found!";
    }
}
