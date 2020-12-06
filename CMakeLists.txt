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
        )

find_package(Boost REQUIRED)

include_directories(src
            libs/jsoncpp
            ${Boost_INCLUDE_DIRS}
        )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
