#include "plugin_a.h"
#include <iostream>

class PluginAImpl : public PluginA {
public:
    std::string execute() override {
        return "Plugin A executed!";
    }
};

extern "C" PluginA* create_plugin() {
    return new PluginAImpl();
}

extern "C" void destroy_plugin(PluginA* plugin) {
    delete plugin;
}
