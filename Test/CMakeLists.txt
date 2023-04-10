cmake_minimum_required(VERSION 3.22)

set(TEST TestPluginManager)

add_executable(${TEST}
    GTestPluginConfigurationParser.cpp
    GTestPluginManager.cpp
)

add_dependencies(${TEST}
    PluginManager
)

target_include_directories(${TEST} PUBLIC ${PluginManager_INCLUDE_DIR})

include(GoogleTestSetup)
FetchGoogleTest(${TEST})
AddGoogleTestDependency(${TEST})
AutoDiscoverTargetTests(${TEST})


####  RKTEMP -- put this back once the core google test framework is running
####
####   set(${test}_HDR
####     ${CMAKE_CURRENT_SOURCE_DIR}/Plugins/Interfaces/IGeneratorManager.h
####     ${CMAKE_CURRENT_SOURCE_DIR}/Plugins/Interfaces/INumberGenerator.h
####     )
####   
####   set(${test}_SRC
####     ${CMAKE_CURRENT_SOURCE_DIR}/GTestPluginManager.cpp
####     ${CMAKE_CURRENT_SOURCE_DIR}/GTestPluginConfigurationParser.cpp
####     )
####   
####   # Install the plugin list config files for the test
####   set(filesToInstall
####     invalidpluginfile.pb.txt
####     notenoughextensions.pb.txt
####     toomanyextensions.pb.txt
####     pluginlist.pb.txt
####     pluginlist_onlyone.pb.txt
####     statefulplugintest.pb.txt
####     )
####   foreach(file ${filesToInstall})
####     install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${file} DESTINATION ${INSTALL_TEST_DIR} COMPONENT monarchtest)
####   endforeach()
####   
####   # Test cases for this unified exe
####   set(${test}_TESTS
####     TestPluginManager
####     TestPluginManagerPathResolution
####     TestPluginConfigurationParser
####     )
####   
####   set(${test}_LIB
####     PluginManager
####     Qt5::Core
####     Qt5::Widgets
####     )
####   
####   AddTestsMacro(${test})
####   
####   # Build the plugins that we depend on
####   add_subdirectory(Plugins/Dummy2GeneratorPlugin)
####   add_subdirectory(Plugins/DummyGeneratorPlugin)
####   add_subdirectory(Plugins/GeneratorManagerPlugin)
####   add_subdirectory(Plugins/UniverseAnswerGeneratorPlugin)
####   add_subdirectory(Plugins/StatefulTestPlugin)
####   
####   add_dependencies(${test}
####     Dummy2GeneratorPlugin
####     DummyGeneratorPlugin
####     GeneratorManagerPlugin
####     UniverseAnswerGeneratorPlugin
####     )
####   
####   configure_file(${CMAKE_CURRENT_SOURCE_DIR}/invalidpluginfile.pb.txt   ${CMAKE_CURRENT_BINARY_DIR}/invalidpluginfile.pb.txt   COPYONLY)
####   configure_file(${CMAKE_CURRENT_SOURCE_DIR}/notenoughextensions.pb.txt ${CMAKE_CURRENT_BINARY_DIR}/notenoughextensions.pb.txt COPYONLY)
####   configure_file(${CMAKE_CURRENT_SOURCE_DIR}/toomanyextensions.pb.txt   ${CMAKE_CURRENT_BINARY_DIR}/toomanyextensions.pb.txt   COPYONLY)
####   configure_file(${CMAKE_CURRENT_SOURCE_DIR}/pluginlist.pb.txt          ${CMAKE_CURRENT_BINARY_DIR}/pluginlist.pb.txt          COPYONLY)
####   configure_file(${CMAKE_CURRENT_SOURCE_DIR}/pluginlist_onlyone.pb.txt  ${CMAKE_CURRENT_BINARY_DIR}/pluginlist_onlyone.pb.txt  COPYONLY)
