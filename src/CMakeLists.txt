cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(nlohmann_json)

file(GLOB netatmoapi_SRCS
    core/naapiclient.cpp
    core/nawsapiclient.cpp
    model/station.cpp
    model/module.cpp
    model/measures.cpp
)

file(GLOB netatmoapi_core_HDRS
    core/naapiclient.h
    core/nawsapiclient.h
)

file(GLOB netatmoapi_core_private_HDRS
    core/scopeexit.hpp
)

file(GLOB netatmoapi_model_HDRS
    model/station.h
    model/module.h
    model/measures.h
    model/params.h
)

file(GLOB netatmoapi_exceptions_HDRS
    exceptions/loginexception.hpp
    exceptions/curlexception.hpp
    exceptions/responseexception.hpp
    exceptions/typenotsupportedexception.hpp
)

add_library(${PROJECT_NAME} SHARED ${netatmoapi_SRCS} ${netatmoapi_core_HDRS} ${netatmoapi_core_private_HDRS} ${netatmoapi_model_HDRS} ${netatmoapi_exceptions_HDRS})

target_link_libraries(${PROJECT_NAME} PRIVATE curl)

install(TARGETS ${PROJECT_NAME} DESTINATION "lib")
install(FILES ${netatmoapi_core_HDRS} DESTINATION "include/netatmo++/core")
install(FILES ${netatmoapi_model_HDRS} DESTINATION "include/netatmo++/model")
install(FILES ${netatmoapi_exceptions_HDRS} DESTINATION "include/netatmo++/exceptions")
