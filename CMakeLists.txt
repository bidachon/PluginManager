cmake_minimum_required(VERSION 3.22)

set (PluginManager_VERSION_MAJOR 2)
set (PluginManager_VERSION_MINOR 0)

project (PluginManager 
    VERSION ${PluginManager_VERSION_MAJOR}.${PluginManager_VERSION_MINOR} 
    DESCRIPTION "A C++ runtime dependency injection framework"
)

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)


add_subdirectory(PluginManager)
add_subdirectory(Test)

enable_testing()

#### RKTODO:  Need to put this stuff back, for now just get it compiling standalone again
# add_subdirectory(Examples)

####  #define a macro to simplify adding tests, then use it
#### macro (do_simpletest name arg result)
####   add_test (${name} ${PluginManager_BINARY_DIR}/PluginManager/Tests/PluginManagerTest ${arg})
####   set_tests_properties (${name}
####     PROPERTIES PASS_REGULAR_EXPRESSION ${result})
#### endmacro (do_simpletest)
#### 
#### 
#### do_simpletest(FileDoesNotExist ${PluginManager_BINARY_DIR}/PluginManager/Tests/XXX.json "File does not exist")
#### do_simpletest(NoConfigurationTag ${PluginManager_BINARY_DIR}/PluginManager/Tests/noconfiguration.json "Missing json object attribute /configuration/")
#### do_simpletest(NoDescriptionTag ${PluginManager_BINARY_DIR}/PluginManager/Tests/nodescription.json "Missing or empty json string attribute /description/")
#### do_simpletest(NoAuthorTag ${PluginManager_BINARY_DIR}/PluginManager/Tests/noauthor.json "Missing or empty json string attribute /author/")
#### do_simpletest(NoPlugins ${PluginManager_BINARY_DIR}/PluginManager/Tests/noplugins.json "Missing or empty json array attribute /plugins/")
#### do_simpletest(InvalidPluginFile ${PluginManager_BINARY_DIR}/PluginManager/Tests/invalidpluginfile.json "The shared library was not found")
#### do_simpletest(NotEnoughExtensions ${PluginManager_BINARY_DIR}/PluginManager/Tests/notenoughextensions.json "This plugin configuration could not provide enough extensions of type -INumberGenerator-")
#### do_simpletest(TooManyExtensions ${PluginManager_BINARY_DIR}/PluginManager/Tests/toomanyextensions.json "This plugin configuration provided too many extensions of type -INumberGenerator-")
