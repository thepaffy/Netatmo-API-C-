include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_BINARY_DIR}/src)

set(parseDevicesTest_SRCS
    main.cpp
    ${PROJECT_SOURCE_DIR}/src/core/parsing.cpp
    ${PROJECT_SOURCE_DIR}/src/model/station.cpp
    ${PROJECT_SOURCE_DIR}/src/model/module.cpp
    ${PROJECT_SOURCE_DIR}/src/model/measures.cpp
    ${PROJECT_SOURCE_DIR}/src/model/place.cpp
)

add_executable(parseDevicesTest ${parseDevicesTest_SRCS})

target_link_libraries(parseDevicesTest
    gtest
)
add_test(parseDevicesTest parseDevicesTest)
