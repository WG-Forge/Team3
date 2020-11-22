cmake_minimum_required(VERSION 3.17)
project(Team3)

set(CMAKE_CXX_STANDARD 14)

include_directories(source-code)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SOURCES
        source-code/main.cpp
        source-code/game/Game.cpp source-code/game/Game.h
        source-code/drawing/Point.h
        source-code/graph/Graph.h source-code/graph/Graph.cpp
        source-code/graph/Node.cpp source-code/graph/Node.h
        source-code/graph/Edge.cpp source-code/graph/Edge.h
        source-code/builder/JSONReader.cpp source-code/builder/JSONReader.h
        source-code/utils/RotationCalculator.cpp source-code/utils/RotationCalculator.h
        source-code/drawing/Renderer.cpp source-code/drawing/Renderer.h 
        source-code/game/Configuration.cpp source-code/game/Configuration.h 
        source-code/graph/City.cpp source-code/graph/City.h 
        source-code/graph/Market.cpp source-code/graph/Market.h 
        source-code/graph/Storage.cpp source-code/graph/Storage.h
        source-code/layout/Layout.h source-code/layout/Layout.cpp
        source-code/game/ServerConnection.cpp source-code/game/ServerConnection.h
        source-code/utils/HexConverter.cpp source-code/utils/HexConverter.h source-code/game/Camera.cpp source-code/game/Camera.h)

add_executable(Team3 ${SOURCES})

target_link_libraries(Team3 ${CONAN_LIBS})