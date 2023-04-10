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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# RKTODO:  Provide ability to create static vs shared library
add_library(${TARGET} STATIC
    ${${TARGET}_SRC}
    ${${TARGET}_HDR}
)

