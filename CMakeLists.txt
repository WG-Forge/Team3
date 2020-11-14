cmake_minimum_required(VERSION 3.17)
project(Team3)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 14)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
)

set(SOURCES
        main.cpp
        MainWindow.cpp MainWindow.h
        Point.h
        DrawingStrategy.h
        MinimalisticDrawingStrategy.cpp MinimalisticDrawingStrategy.h
        GraphView.cpp GraphView.h
        Graph.h
        Node.cpp Node.h Edge.cpp Edge.h Graph.cpp)

qt5_wrap_ui(SOURCES mainwindow.ui)

add_executable(Team3 ${SOURCES})

target_link_libraries(Team3 Qt5::Widgets)