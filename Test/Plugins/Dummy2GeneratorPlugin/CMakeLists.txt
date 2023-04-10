set(TARGET Dummy2GeneratorPlugin)

set(${TARGET}_HDR
  ${CMAKE_CURRENT_SOURCE_DIR}/DummyGenerator.h
  ${CMAKE_CURRENT_SOURCE_DIR}/DummyGeneratorPlugin.h
  )

set(${TARGET}_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/DummyGenerator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/DummyGeneratorPlugin.cpp
  )

set(${TARGET}_INC
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  )

set(${TARGET}_LIB
  PluginManager
  )

CreatePluginMacro(${TARGET} TEST)

