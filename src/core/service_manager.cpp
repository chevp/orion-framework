#include "service_manager.h"
#include <iostream>
#include <dlfcn.h>

ServiceManager::~ServiceManager() {
    // Beim Zerstören des ServiceManagers werden alle Plugins entfernt.
    for (auto& plugin : plugins) {
        unloadPlugin(plugin.first);
    }
}

bool ServiceManager::loadPlugin(const std::string& pluginName, const std::string& path) {
    // Plugin dynamisch laden
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Error loading plugin " << pluginName << ": " << dlerror() << std::endl;
        return false;
    }

    // Plugin-Factory-Funktionen abrufen
    auto createPlugin = (PluginInterface* (*)()) dlsym(handle, "create_plugin");
    if (!createPlugin) {
        std::cerr << "Error finding 'create_plugin' function in " << pluginName << ": " << dlerror() << std::endl;
        dlclose(handle);
        return false;
    }

    // Plugin erstellen
    std::shared_ptr<PluginInterface> plugin(createPlugin(), [handle](PluginInterface*) { dlclose(handle); });
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
