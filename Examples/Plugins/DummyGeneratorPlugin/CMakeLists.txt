
add_library( DummyGeneratorPlugin SHARED
			DummyGeneratorPlugin.cpp
			DummyGenerator.cpp
			)


target_include_directories (DummyGeneratorPlugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include_directories ("${PROJECT_SOURCE_DIR}/PluginManager/")

set_target_properties( DummyGeneratorPlugin
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
)

# Use the Xml module from Qt 5.
target_link_libraries(DummyGeneratorPlugin Qt5::Core PluginManager)