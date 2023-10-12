set(TARGET UniverseAnswerGeneratorPlugin)

set(${TARGET}_HDR
  ${CMAKE_CURRENT_SOURCE_DIR}/UniverseAnswerGeneratorImpl.h
  ${CMAKE_CURRENT_SOURCE_DIR}/UniverseAnswerGeneratorPlugin.h
  )

set(${TARGET}_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/UniverseAnswerGeneratorImpl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/UniverseAnswerGeneratorPlugin.cpp
  )

set(${TARGET}_INC
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  )

set(${TARGET}_LIB
  PluginManager
  )

CreatePluginMacro(${TARGET} TEST)

