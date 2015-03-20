cmake_minimum_required (VERSION 2.6)

project (PluginManager)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

#set (CMAKE_PREFIX_PATH)
#message("CMAKE_PREFIX_PATH:" ${CMAKE_PREFIX_PATH} )

set (CMAKE_PREFIX_PATH "/home/nicolasrobert/Programming/Qt5.4.0/5.4/gcc_64/lib/cmake/" )

# Find the QtXml library
find_package(Qt5Xml)
find_package(Qt5Widgets)

#version number
set (PluginManager_VERSION_MAJOR 1)
set (PluginManager_VERSION_MINOR 0)


add_subdirectory(PluginManager)
add_subdirectory(Apps)
add_subdirectory(Plugins)

#message( "PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR} )