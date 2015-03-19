add_library( UniverseAnswerGeneratorPlugin SHARED universeanswergeneratorimpl.cpp 
			universeanswergeneratorplugin.cpp 
			)


target_include_directories (UniverseAnswerGeneratorPlugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
include_directories ("${PROJECT_SOURCE_DIR}/PluginManager/Interfaces")

#message("INCLUDE_DIRECTORIES" ${PROJECT_SOURCE_DIR}/PluginManager/Interfaces/inumbergenerator.h)

# Use the Xml module from Qt 5.
target_link_libraries(UniverseAnswerGeneratorPlugin Qt5::Core)