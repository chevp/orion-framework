#include <iostream>
#include <dlfcn.h>
#include "core/service_manager.h"

typedef void* (*CreatePluginFunc)();
typedef void (*DestroyPluginFunc)(void*);

int main() {
    // Laden der Plugins
    void* pluginAHandle = dlopen("./build/plugin_a.so", RTLD_LAZY);
    void* pluginBHandle = dlopen("./build/plugin_b.so", RTLD_LAZY);

    if (!pluginAHandle || !pluginBHandle) {
        std::cerr << "Error loading plugins: " << dlerror() << std::endl;
        return 1;
    }

    // Zugriff auf die Plugin-Funktionen
    CreatePluginFunc createPluginA = (CreatePluginFunc) dlsym(pluginAHandle, "create_plugin");
    DestroyPluginFunc destroyPluginA = (DestroyPluginFunc) dlsym(pluginAHandle, "destroy_plugin");

    CreatePluginFunc createPluginB = (CreatePluginFunc) dlsym(pluginBHandle, "create_plugin");
    DestroyPluginFunc destroyPluginB = (DestroyPluginFunc) dlsym(pluginBHandle, "destroy_plugin");

    // Plugin-Instanzen erstellen und verwenden
    void* pluginA = createPluginA();
    void* pluginB = createPluginB();

    std::cout << "Plugin A: " << static_cast<PluginA*>(pluginA)->execute() << std::endl;
    std::cout << "Plugin B: " << static_cast<PluginB*>(pluginB)->execute() << std::endl;

    // Plugins zerstören
    destroyPluginA(pluginA);
    destroyPluginB(pluginB);

    // Schließen der Plugin-DLLs
    dlclose(pluginAHandle);
    dlclose(pluginBHandle);

    return 0;
}
