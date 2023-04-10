set(TARGET StatefulTestPlugin)

set(${TARGET}_HDR
    ${CMAKE_CURRENT_SOURCE_DIR}/StatefulTestClass.h
    ${CMAKE_CURRENT_SOURCE_DIR}/StatefulTestPlugin.h
  )

set(${TARGET}_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/StatefulTestClass.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatefulTestPlugin.cpp
  )

set(${TARGET}_INC
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  )

set(${TARGET}_LIB
  PluginManager
  )

CreatePluginMacro(${TARGET} TEST)

