cmake_minimum_required(VERSION 3.5.0)

project(utilsTest)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../src)

file(GLOB utilsTest_SRCS
    main.cpp
)

add_executable(${PROJECT_NAME} ${utilsTest_SRCS})

target_link_libraries(${PROJECT_NAME}
    netatmoapi++
    gtest
)
add_test(utilsTest utilsTest)
