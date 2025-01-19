#include <iostream>
#include <windows.h>
#include "core/service_manager.h"

// Function pointer types for plugin creation and destruction
typedef void* (*CreatePluginFunc)();
typedef void (*DestroyPluginFunc)(void*);

int main() {
    // Laden der Plugins (DLLs auf Windows)
    HMODULE pluginAHandle = LoadLibrary("plugin_a.dll");
    HMODULE pluginBHandle = LoadLibrary("plugin_b.dll");

    if (!pluginAHandle || !pluginBHandle) {
        std::cerr << "Error loading plugins: " << GetLastError() << std::endl;
        return 1;
    }

    // Zugriff auf die Plugin-Funktionen
    CreatePluginFunc createPluginA = (CreatePluginFunc)GetProcAddress(pluginAHandle, "create_plugin");
    DestroyPluginFunc destroyPluginA = (DestroyPluginFunc)GetProcAddress(pluginAHandle, "destroy_plugin");

    CreatePluginFunc createPluginB = (CreatePluginFunc)GetProcAddress(pluginBHandle, "create_plugin");
    DestroyPluginFunc destroyPluginB = (DestroyPluginFunc)GetProcAddress(pluginBHandle, "destroy_plugin");

    // Überprüfen, ob alle Funktionen geladen wurden
    if (!createPluginA || !destroyPluginA || !createPluginB || !destroyPluginB) {
        std::cerr << "Error finding functions in plugins!" << std::endl;
        FreeLibrary(pluginAHandle);
        FreeLibrary(pluginBHandle);
        return 1;
    }

    // Plugin-Instanzen erstellen und verwenden
    void* pluginA = createPluginA();
    void* pluginB = createPluginB();

    // Falls PluginA und PluginB C++-Objekte sind, könnte eine Typumwandlung notwendig sein
    // Beispiel: std::cout << "Plugin A: " << static_cast<PluginA*>(pluginA)->execute() << std::endl;
    // Beispiel: std::cout << "Plugin B: " << static_cast<PluginB*>(pluginB)->execute() << std::endl;

    std::cout << "Plugin A and Plugin B executed successfully." << std::endl;

    // Plugins zerstören
    destroyPluginA(pluginA);
    destroyPluginB(pluginB);

    // Schließen der Plugin-DLLs
    FreeLibrary(pluginAHandle);
    FreeLibrary(pluginBHandle);

    return 0;
}
