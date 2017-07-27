cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(nlohmann_json)

file(GLOB netatmoapi_SRCS
    naapiclient.cpp
    nawsapiclient.cpp
    station.cpp
    module.cpp
    measures.cpp
)

file(GLOB netatmoapi_HDRS
    naapiclient.h
    nawsapiclient.h
    station.h
    module.h
    measures.h
    loginexception.hpp
    curlexception.hpp
    responseexception.hpp
    scopeexit.hpp
)

add_library(${PROJECT_NAME} SHARED ${netatmoapi_SRCS} ${netatmoapi_HDRS})

target_link_libraries(${PROJECT_NAME} PRIVATE curl)

install(TARGETS ${PROJECT_NAME} DESTINATION "lib")
install(FILES ${netatmoapi_HDRS} DESTINATION "include/netatmo++")
