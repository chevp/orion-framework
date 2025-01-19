cmake_minimum_required(VERSION 3.10)
project(MicroserviceArchitecture)

set(CMAKE_CXX_STANDARD 17)

# Verzeichnisse für die C++-Quellen
include_directories(src)

# Hauptprogramm kompilieren
add_executable(microservice-app src/main.cpp src/core/service_manager.cpp)

# Microservice-Module als Shared Libraries kompilieren
add_subdirectory(src/modules/plugin_a)
add_subdirectory(src/modules/plugin_b)

# Ziel für das Hauptprogramm mit den Plugin-Dependencies
target_link_libraries(microservice-app
    plugin_a
    plugin_b
)