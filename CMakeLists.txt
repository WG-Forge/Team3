cmake_minimum_required(VERSION 3.17)
project(Team3)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML REQUIRED
        system
        window
        graphics
        network
        audio)

set(SOURCES
        source-code/main.cpp
        source-code/game/Game.cpp source-code/game/Game.h
        source-code/drawing/Point.h
        source-code/graph/Graph.h
        source-code/graph/Node.cpp source-code/graph/Node.h
        source-code/graph/Edge.cpp source-code/graph/Edge.h
        source-code/graph/Graph.cpp
        libraries/dist/json/json.h libraries/dist/json/json-forwards.h libraries/dist/jsoncpp.cpp
        source-code/builder/JSONReader.cpp source-code/builder/JSONReader.h
        source-code/drawing/RotationCalculator.cpp source-code/drawing/RotationCalculator.h
        source-code/drawing/Renderer.cpp source-code/drawing/Renderer.h source-code/game/Configuration.cpp source-code/game/Configuration.h)

add_executable(Team3 ${SOURCES})

target_link_libraries(Team3
        sfml-graphics
        sfml-window
        sfml-system
        sfml-network
        sfml-audio)
