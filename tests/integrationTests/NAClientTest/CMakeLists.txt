include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_BINARY_DIR}/src)

set(NAClientTest_SRCS
    main.cpp
)

add_executable(NAClientTest ${NAClientTest_SRCS})

target_link_libraries(NAClientTest
    netatmoapi++
    gtest
)
add_test(NAClientTest NAClientTest)
