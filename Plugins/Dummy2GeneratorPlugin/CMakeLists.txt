
add_library( Dummy2GeneratorPlugin SHARED
			DummyGeneratorPlugin.cpp
			DummyGenerator.cpp
			)


target_include_directories (Dummy2GeneratorPlugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include_directories ("${PROJECT_SOURCE_DIR}/PluginManager/")

set_target_properties( Dummy2GeneratorPlugin
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
)

# Use the Xml module from Qt 5.
target_link_libraries(Dummy2GeneratorPlugin Qt5::Core PluginManager)