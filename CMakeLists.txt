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
        drawing/Point.h
        drawing/DrawingStrategy.h
        drawing/MinimalisticDrawingStrategy.cpp drawing/MinimalisticDrawingStrategy.h
        view/GraphView.cpp view/GraphView.h
        graph/Graph.h
        graph/Node.cpp graph/Node.h
        graph/Edge.cpp graph/Edge.h
        graph/Graph.cpp
        drawing/Shape.cpp drawing/Shape.h
        libraries/dist/json/json.h libraries/dist/json/json-forwards.h libraries/dist/jsoncpp.cpp
        drawing/Circle.cpp drawing/Circle.h
        drawing/Line.cpp drawing/Line.h
        drawing/DrawingStrategy.cpp
        drawing/ClassicalDrawingStrategy.cpp drawing/ClassicalDrawingStrategy.h
        builder/JSONReader.cpp builder/JSONReader.h
        drawing/RotationCalculator.cpp drawing/RotationCalculator.h)

qt5_wrap_ui(SOURCES mainwindow.ui)
qt5_add_resources(SOURCES resources.qrc)

add_executable(Team3 ${SOURCES})

target_link_libraries(Team3 Qt5::Widgets)