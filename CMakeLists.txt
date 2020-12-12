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

        src/Point.h
        src/Observer.cpp src/Observer.h
        src/graph-components/Node.cpp src/graph-components/Node.h
        src/graph-components/Town.cpp src/graph-components/Town.h
        src/graph-components/Market.cpp src/graph-components/Market.h
        src/graph-components/Storage.cpp src/graph-components/Storage.h
        src/graph-components/Edge.cpp src/graph-components/Edge.h
        src/graph-components/EdgeCreationHelper.h
        src/networking-components/Request.h
        src/networking-components/Response.h
        src/networking-components/JSONReader.cpp src/networking-components/JSONReader.h
        src/agents/GraphAgent.cpp src/agents/GraphAgent.h
        src/agents/ServerConnectorAgent.cpp src/agents/ServerConnectorAgent.h
        src/game-components/Player.cpp src/game-components/Player.h
        src/configs/defines.h
        src/game-components/Train.cpp src/game-components/Train.h
        src/game-components/Event.h
        )

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
        libs/jsoncpp
        ${Boost_INCLUDE_DIRS}
        )

add_executable(${PROJECT_NAME} ${SOURCES} ${WIN32_SOURCES})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBRARIES})
endif()

if(APPLE)
    target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
endif()
