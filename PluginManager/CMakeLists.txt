set (PluginManager_SOURCE pluginconfigurationparser.cpp
 pluginmanager.cpp
)


add_library( PluginManager STATIC ${PluginManager_SOURCE})

target_include_directories (PluginManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Use the Xml module from Qt 5.
target_link_libraries(PluginManager Qt5::Xml)

add_subdirectory(Tests)





