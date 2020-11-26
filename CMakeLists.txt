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
        source-code/components/graph/Graph.h source-code/components/graph/Graph.cpp
        source-code/components/graph/Node.cpp source-code/components/graph/Node.h
        source-code/components/graph/Edge.cpp source-code/components/graph/Edge.h
        source-code/builder/JSONReader.cpp source-code/builder/JSONReader.h
        source-code/utils/RotationCalculator.cpp source-code/utils/RotationCalculator.h
        source-code/drawing/Renderer.cpp source-code/drawing/Renderer.h 
        source-code/game/Configuration.cpp source-code/game/Configuration.h
        source-code/components/map-objects/City.cpp source-code/components/map-objects/City.h
        source-code/components/map-objects/Market.cpp source-code/components/map-objects/Market.h
        source-code/components/map-objects/Storage.cpp source-code/components/map-objects/Storage.h
        source-code/layout/Layout.h source-code/layout/Layout.cpp
        source-code/game/ServerConnection.cpp source-code/game/ServerConnection.h
        source-code/utils/HexConverter.cpp source-code/utils/HexConverter.h
        source-code/components/map-objects/Train.cpp source-code/components/map-objects/Train.h
        source-code/components/map-objects/Post.cpp source-code/components/map-objects/Post.h
        source-code/components/static/StaticStore.h source-code/components/static/StaticStore.cpp)

add_executable(Team3 ${SOURCES})

target_link_libraries(Team3 ${CONAN_LIBS})