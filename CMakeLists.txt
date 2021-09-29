cmake_minimum_required(VERSION 3.20)
project(GViewer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(
        GViewer
        main.cpp
        Utils/Containers/Vector.h++
        Exceptions/Exception.h++ Exceptions/Memory.h++ Exceptions/Range.h++ Utils/BaseObject.h++)

target_link_libraries(GViewer
        PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

