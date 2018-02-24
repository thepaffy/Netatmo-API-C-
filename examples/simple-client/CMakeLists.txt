cmake_minimum_required(VERSION 3.5.0)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_BINARY_DIR}/src)

set(example_SRCS
    main.cpp
)

add_executable(simple-client ${example_SRCS})

target_link_libraries(simple-client netatmoapi++)
install(TARGETS simple-client DESTINATION ${INSTALL_BIN_DIR})
