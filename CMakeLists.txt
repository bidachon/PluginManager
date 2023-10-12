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

option(PLUGIN_MANAGER_BUILD_TESTS "Build unit tests" ON)
if(PLUGIN_MANAGER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(Test)
endif()

