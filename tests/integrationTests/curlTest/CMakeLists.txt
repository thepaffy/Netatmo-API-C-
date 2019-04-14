include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_BINARY_DIR}/src)

set(curlTest_SRCS
    main.cpp
)

add_executable(curlTest ${curlTest_SRCS})

target_link_libraries(curlTest
    gtest
    curl
)
add_test(curlTest curlTest)
