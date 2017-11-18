cmake_minimum_required(VERSION 3.5.0)

project(simple-wa-client)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../src)

file(GLOB example_SRCS
    main.cpp
)

add_executable(${PROJECT_NAME} ${example_SRCS})

target_link_libraries(${PROJECT_NAME} netatmoapi++)
install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_BIN_DIR})
