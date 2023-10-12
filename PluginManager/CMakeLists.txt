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

# RKTODO:  Provide ability to create static vs shared library
add_library(${TARGET} STATIC
    ${${TARGET}_SRC}
    ${${TARGET}_HDR}
)

set_target_properties(${TARGET} PROPERTIES VERSION ${PluginManager_VERSION_MAJOR}.${PluginManager_VERSION_MINOR})
set_target_properties(${TARGET} PROPERTIES SOVERSION ${PluginManager_VERSION_MAJOR})

target_include_directories(${TARGET}
    PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}"
  )

