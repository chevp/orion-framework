add_library(plugin_b SHARED plugin_b.cpp)
target_include_directories(plugin_b PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
