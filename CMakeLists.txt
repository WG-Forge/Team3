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
        source-code/main.cpp
        source-code/MainWindow.cpp source-code/MainWindow.h
        source-code/drawing/Point.h
        source-code/drawing/DrawingStrategy.h
        source-code/drawing/MinimalisticDrawingStrategy.cpp source-code/drawing/MinimalisticDrawingStrategy.h
        source-code/view/GraphView.cpp source-code/view/GraphView.h
        source-code/graph/Graph.h
        source-code/graph/Node.cpp source-code/graph/Node.h
        source-code/graph/Edge.cpp source-code/graph/Edge.h
        source-code/graph/Graph.cpp
        source-code/drawing/Shape.cpp source-code/drawing/Shape.h
        libraries/dist/json/json.h libraries/dist/json/json-forwards.h libraries/dist/jsoncpp.cpp
        source-code/drawing/Circle.cpp source-code/drawing/Circle.h
        source-code/drawing/Line.cpp source-code/drawing/Line.h
        source-code/drawing/DrawingStrategy.cpp
        source-code/drawing/ClassicalDrawingStrategy.cpp source-code/drawing/ClassicalDrawingStrategy.h
        source-code/builder/JSONReader.cpp source-code/builder/JSONReader.h
        source-code/drawing/RotationCalculator.cpp source-code/drawing/RotationCalculator.h)

qt5_wrap_ui(SOURCES source-code/mainwindow.ui)
qt5_add_resources(SOURCES resources.qrc)

add_executable(Team3 ${SOURCES})

target_link_libraries(Team3 Qt5::Widgets)