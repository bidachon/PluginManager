add_executable(ExampleApp main.cpp mainwindow.cpp mainwindow.ui)

# Generate code from ui files
qt5_wrap_ui(UI_HEADERS mainwindow.ui)

target_include_directories (ExampleApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/pluginlist.json ${CMAKE_CURRENT_BINARY_DIR}/pluginlist.json)

target_link_libraries(ExampleApp PluginManager Qt5::Widgets )