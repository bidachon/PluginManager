set(TARGET GeneratorManagerPlugin)

set(${TARGET}_HDR
  ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorManagerImpl.h
  ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorManagerPlugin.h
  )

set(${TARGET}_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorManagerImpl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/GeneratorManagerPlugin.cpp
  )

set(${TARGET}_INC
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  )

set(${TARGET}_LIB
  PluginManager
  Qt5::Widgets
  )

CreatePluginMacro(${TARGET} TEST)
