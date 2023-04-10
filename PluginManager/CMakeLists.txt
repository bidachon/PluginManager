set(TARGET PluginManager)

set(${TARGET}_HDR
  ${CMAKE_CURRENT_SOURCE_DIR}/Dependency.h
  ${CMAKE_CURRENT_SOURCE_DIR}/InterfaceId.h
  ${CMAKE_CURRENT_SOURCE_DIR}/PluginManager.h
  ${CMAKE_CURRENT_SOURCE_DIR}/StdPluginLib.h
  ${CMAKE_CURRENT_SOURCE_DIR}/IPluginLib.h
  ${CMAKE_CURRENT_SOURCE_DIR}/IPluginInterface.h
  ${CMAKE_CURRENT_SOURCE_DIR}/PluginConfigurationParser.h
  ${CMAKE_CURRENT_SOURCE_DIR}/PluginUtils.h
  )

set(${TARGET}_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/PluginConfigurationParser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PluginManager.cpp
  )

set(${TARGET}_INC
  ${CMAKE_CURRENT_BINARY_DIR}/Config
  )

set(${TARGET}_LIB
  )

# RKTODO:  Provide ability to create static vs shared library
add_library(${TARGET} STATIC
    ${${TARGET}_SRC}
    ${${TARGET}_HDR}
)

set_target_properties(${TARGET} PROPERTIES VERSION ${PluginManager_VERSION_MAJOR}.${PluginManager_VERSION_MINOR})
set_target_properties(${TARGET} PROPERTIES SOVERSION ${PluginManager_VERSION_MAJOR})

set(${TARGET}_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE INTERNAL "" FORCE)

