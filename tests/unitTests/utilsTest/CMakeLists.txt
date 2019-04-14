include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_BINARY_DIR}/src)

set(utilsTest_SRCS
    main.cpp
    ${PROJECT_SOURCE_DIR}/src/core/utils.cpp
)

add_executable(utilsTest ${utilsTest_SRCS})

target_link_libraries(utilsTest
    gtest
)
add_test(utilsTest utilsTest)
