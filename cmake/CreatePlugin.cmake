# Create a plugin library
#
# This macro creates a plugin library with the given name and type.
#
# PLUGIN: The name of the plugin library to create
# PLUGIN_TYPE:  The type of plugin to create.  This is used to determine the
#               installation location of the plugin.  Valid values are:
#
#               - "TEST":  This is a test plugin.  It will be installed in the
#                          test plugin directory.
#
macro(CreatePluginMacro PLUGIN PLUGIN_TYPE)
    string(COMPARE EQUAL "${PLUGIN_TYPE}" TEST _cmp)
    if(NOT _cmp)
        message(FATAL_ERROR "Invalid plugin type: ${PLUGIN_TYPE} for plugin ${PLUGIN}")
    endif()

    message("Creating plugin ${PLUGIN}")

    add_library(${PLUGIN} SHARED
            ${${PLUGIN}_SRC}
            ${${PLUGIN}_HDR}
        )

    target_link_libraries(${PLUGIN} PUBLIC
            ${${PLUGIN}_LIB}
        )

    message(VERBOSE "Adding include directories for ${PLUGIN}: ${${PLUGIN}_INC}")
    target_include_directories(${PLUGIN}
        PRIVATE
            ${${PLUGIN}_INC}
        )

    foreach(LIB ${${PLUGIN}_LIB})
        message(VERBOSE "Adding include directories for ${PLUGIN}: $<TARGET_PROPERTY:${LIB},INTERFACE_INCLUDE_DIRECTORIES>")
        target_include_directories(${PLUGIN}
            PRIVATE
            $<TARGET_PROPERTY:${LIB},INTERFACE_INCLUDE_DIRECTORIES>
            )
    endforeach()

    # See the if statement at the top, this assumes that the plugin type is TEST for now
    message(VERBOSE "Copying test plugin ${PLUGIN}")
    add_custom_command(TARGET ${PLUGIN} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PLUGIN}> ${CMAKE_BINARY_DIR}/Test/plugins
        )

endmacro()
