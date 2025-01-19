#ifndef PLUGIN_A_H
#define PLUGIN_A_H

#include <string>

class PluginA {
public:
    virtual ~PluginA() {}
    virtual std::string execute() = 0;
};

extern "C" {
    PluginA* create_plugin();
    void destroy_plugin(PluginA* plugin);
}

#endif // PLUGIN_A_H
