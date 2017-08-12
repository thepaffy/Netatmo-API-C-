cmake_minimum_required(VERSION 3.1.0)

project(curlTest)
find_package(nlohmann_json)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB curlTest_SRCS
    main.cpp
)

add_executable(${PROJECT_NAME} ${curlTest_SRCS})

target_link_libraries(${PROJECT_NAME}
    gtest
    curl
)
add_test(curlTest curlTest)
