## RKTODO : sticking this block here temporarily until I figure out whether 
##          I need it later... moved from the top level file
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Find the QtXml library
find_package(Qt5Xml)
find_package(Qt5Widgets)


add_subdirectory(Plugins)
add_subdirectory(ExampleApp)
