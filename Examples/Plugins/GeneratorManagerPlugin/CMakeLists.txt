add_library( GeneratorManagerPlugin SHARED
			generatormanagerplugin.cpp
			generatormanagerimpl.cpp
			)


target_include_directories (GeneratorManagerPlugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include_directories ("${PROJECT_SOURCE_DIR}/PluginManager/Interfaces")

set_target_properties( GeneratorManagerPlugin
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
)


# Use the Xml module from Qt 5.
target_link_libraries(GeneratorManagerPlugin Qt5::Core Qt5::Widgets PluginManager)