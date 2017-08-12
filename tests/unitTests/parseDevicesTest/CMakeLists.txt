cmake_minimum_required(VERSION 3.5.0)

project(parseDevicesTest)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../src)

file(GLOB parseDevicesTest_SRCS
    main.cpp
)

add_executable(${PROJECT_NAME} ${parseDevicesTest_SRCS})

target_link_libraries(${PROJECT_NAME}
    netatmoapi++
    gtest
)
add_test(parseDevicesTest parseDevicesTest)
