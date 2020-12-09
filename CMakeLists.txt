cmake_minimum_required(VERSION 3.17)

set(PROJECT_NAME Team3)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0xA600")
endif()

set(SOURCES
        main.cpp
        libs/jsoncpp/jsoncpp.cpp

        src/Point.h
        src/Observer.cpp src/Observer.h
        src/graph-components/Node.cpp src/graph-components/Node.h
        src/graph-components/Town.cpp src/graph-components/Town.h
        src/graph-components/Market.cpp src/graph-components/Market.h
        src/graph-components/Storage.cpp src/graph-components/Storage.h
        src/graph-components/Edge.cpp src/graph-components/Edge.h
        src/networking-components/Request.h
        src/networking-components/Response.h
        src/networking-components/JSONParser.cpp src/networking-components/JSONParser.h
        src/agents/GraphAgent.cpp src/agents/GraphAgent.h
        src/agents/ServerConnectorAgent.cpp src/agents/ServerConnectorAgent.h
        src/Player.h src/Player.cpp
        src/configs/defines.h)

find_package(Boost REQUIRED)

include_directories(
        src
        src/agents
        src/configs
        src/graph-components
        src/networking-components
        libs/jsoncpp
        ${Boost_INCLUDE_DIRS}
        )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
