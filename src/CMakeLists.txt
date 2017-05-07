cmake_minimum_required(VERSION 3.1.0)

include_directories (${CMAKE_CURRENT_BINARY_DIR})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_definitions(-std=c++14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
find_package(nlohmann_json)

file(GLOB netatmoapi_SRCS
    naapiclient.cpp
    station.cpp
    module.cpp
    measures.cpp
)

file(GLOB netatmoapi_HDRS
    naapiclient.h
    station.h
    module.h
    measures.h
)

add_library(${PROJECT_NAME} SHARED ${netatmoapi_SRCS})

target_link_libraries(${PROJECT_NAME} curl)
