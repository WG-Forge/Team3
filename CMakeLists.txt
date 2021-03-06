cmake_minimum_required(VERSION 3.17)

set(PROJECT_NAME Team3)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0xA600")
endif()

if(APPLE)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

set(SOURCES
        main.cpp

        src/configs/defines.h
        src/Observer.cpp src/Observer.h
        src/graph-components/Node.cpp src/graph-components/Node.h
        src/graph-components/Town.cpp src/graph-components/Town.h
        src/graph-components/Market.cpp src/graph-components/Market.h
        src/graph-components/Storage.cpp src/graph-components/Storage.h
        src/graph-components/Edge.cpp src/graph-components/Edge.h
        src/graph-components/EdgeCreationHelper.h
        src/graph-components/Hometown.cpp src/graph-components/Hometown.h
        src/networking-components/Request.h
        src/networking-components/Response.h
        src/networking-components/JSONReader.cpp src/networking-components/JSONReader.h
        src/game-components/Player.cpp src/game-components/Player.h
        src/game-components/Train.cpp src/game-components/Train.h
        src/render-components/Point.h
        src/render-components/RotationCalculator.cpp src/render-components/RotationCalculator.h
        src/render-components/Configuration.cpp src/render-components/Configuration.h
        src/render-components/Camera.cpp src/render-components/Camera.h
        src/render-components/Renderer.cpp src/render-components/Renderer.h
        src/render-components/ResourceManager.cpp src/render-components/ResourceManager.h
        src/render-components/GameMapConfig.cpp src/render-components/GameMapConfig.h
        src/agents/RenderAgent.cpp src/agents/RenderAgent.h
        src/agents/TrainsAgent.cpp src/agents/TrainsAgent.h
        src/agents/MoveAgent.cpp src/agents/MoveAgent.h
        src/agents/GraphAgent.cpp src/agents/GraphAgent.h
        src/agents/ServerConnectorAgent.cpp src/agents/ServerConnectorAgent.h
        src/agents/UpgradeAgent.cpp src/agents/UpgradeAgent.h)

if(WIN32)
    set(WIN32_SOURCES libs/jsoncpp/jsoncpp.cpp)

    find_package(Boost REQUIRED)
    find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
endif()

include_directories(
        src
        src/agents
        src/configs
        src/game-components
        src/graph-components
        src/networking-components
        src/render-components
        libs/jsoncpp
        ${Boost_INCLUDE_DIRS}
        )

add_executable(${PROJECT_NAME} ${SOURCES} ${WIN32_SOURCES})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)
endif()

if(APPLE)
    target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
endif()
