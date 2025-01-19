#ifndef PLUGIN_B_H
#define PLUGIN_B_H

#include <string>  // For std::string

// This is the interface that all plugins must implement.
class PluginInterface {
public:
    virtual ~PluginInterface() = default;
    virtual std::string execute() = 0;  // The function to be implemented by plugins
};

// Exported functions for creating and destroying the plugin instance
extern "C" __declspec(dllexport) PluginInterface* create_plugin();  // Creates a new plugin instance
extern "C" __declspec(dllexport) void destroy_plugin(PluginInterface* plugin);  // Destroys the plugin instance

#endif // PLUGIN_B_H
