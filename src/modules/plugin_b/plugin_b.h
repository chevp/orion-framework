#ifndef PLUGIN_B_H
#define PLUGIN_B_H

#include <string>

class PluginB {
public:
    virtual ~PluginB() {}
    virtual std::string execute() = 0;
};

extern "C" {
    PluginB* create_plugin();
    void destroy_plugin(PluginB* plugin);
}

#endif // PLUGIN_B_H
