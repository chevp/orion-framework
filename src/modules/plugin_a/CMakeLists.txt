add_library(plugin_a SHARED plugin_a.cpp)
target_include_directories(plugin_a PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})