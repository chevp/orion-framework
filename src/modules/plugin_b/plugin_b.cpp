#include "plugin_b.h"
#include <iostream>

class PluginBImpl : public PluginB {
public:
    std::string execute() override {
        return "Plugin B executed!";
    }
};

extern "C" PluginB* create_plugin() {
    return new PluginBImpl();
}

extern "C" void destroy_plugin(PluginB* plugin) {
    delete plugin;
}
