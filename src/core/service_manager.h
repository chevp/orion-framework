#ifndef SERVICE_MANAGER_H
#define SERVICE_MANAGER_H

#include <string>
#include <unordered_map>
#include <memory>

class PluginInterface {
public:
    virtual ~PluginInterface() {}
    virtual std::string execute() = 0;
};

// Manager für die Plugins
class ServiceManager {
public:
    ServiceManager() = default;
    ~ServiceManager();

    // Plugin laden
    bool loadPlugin(const std::string& pluginName, const std::string& path);
    // Plugin entfernen
    void unloadPlugin(const std::string& pluginName);
    // Plugin ausführen
    std::string executePlugin(const std::string& pluginName);

private:
    std::unordered_map<std::string, std::shared_ptr<PluginInterface>> plugins;
};

#endif // SERVICE_MANAGER_H
