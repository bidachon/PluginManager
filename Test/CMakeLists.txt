set(TEST TestPluginManager)

add_executable(${TEST}
    GTestPluginConfigurationParser.cpp
    GTestPluginManager.cpp
)

target_include_directories(${TEST}
    PRIVATE
    $<TARGET_PROPERTY:PluginManager,INTERFACE_INCLUDE_DIRECTORIES>
    )

target_link_libraries(${TEST} PRIVATE
    PluginManager
    )

include(GoogleTestSetup)
FetchGoogleTest(${TEST})
AddGoogleTestDependency(${TEST})
AutoDiscoverTargetTests(${TEST})

add_subdirectory(Plugins)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/invalidpluginfile.pb.txt   ${CMAKE_CURRENT_BINARY_DIR}/invalidpluginfile.pb.txt   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/notenoughextensions.pb.txt ${CMAKE_CURRENT_BINARY_DIR}/notenoughextensions.pb.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/toomanyextensions.pb.txt   ${CMAKE_CURRENT_BINARY_DIR}/toomanyextensions.pb.txt   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/pluginlist.pb.txt          ${CMAKE_CURRENT_BINARY_DIR}/pluginlist.pb.txt          COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/pluginlist_onlyone.pb.txt  ${CMAKE_CURRENT_BINARY_DIR}/pluginlist_onlyone.pb.txt  COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/statefulplugintest.pb.txt  ${CMAKE_CURRENT_BINARY_DIR}/statefulplugintest.pb.txt  COPYONLY)

