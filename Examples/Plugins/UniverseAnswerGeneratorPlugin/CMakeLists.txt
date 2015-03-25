
add_library( UniverseAnswerGeneratorPlugin SHARED
			universeanswergeneratorplugin.cpp
			universeanswergeneratorimpl.cpp
			)


target_include_directories (UniverseAnswerGeneratorPlugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include_directories ("${PROJECT_SOURCE_DIR}/PluginManager/Interfaces")

set_target_properties( UniverseAnswerGeneratorPlugin
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
)

# Use the Xml module from Qt 5.
target_link_libraries(UniverseAnswerGeneratorPlugin Qt5::Core PluginManager)