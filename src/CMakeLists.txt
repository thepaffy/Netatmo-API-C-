cmake_minimum_required(VERSION 3.5.0)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(nlohmann_json REQUIRED)

set(${PROJECT_NAME}_VERSION_MAJOR 2)
set(${PROJECT_NAME}_VERSION_STRING ${${PROJECT_NAME}_VERSION_MAJOR})

file(GLOB netatmoapi_SRCS
    core/naapiclient.cpp
    core/nahccapiclient.cpp
    core/nawsapiclient.cpp
    core/utils.cpp
    model/station.cpp
    model/module.cpp
    model/measures.cpp
)

file(GLOB netatmoapi_core_HDRS
    core/naapiclient.h
    core/nahccapiclient.h
    core/nawsapiclient.h
    core/utils.h
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
)

add_library(${PROJECT_NAME} SHARED ${netatmoapi_SRCS} ${netatmoapi_core_HDRS} ${netatmoapi_core_private_HDRS} ${netatmoapi_model_HDRS} ${netatmoapi_exceptions_HDRS})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${${PROJECT_NAME}_VERSION_STRING} SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR})
target_link_libraries(${PROJECT_NAME} PRIVATE curl)

install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_LIB_DIR})
install(FILES ${netatmoapi_core_HDRS} DESTINATION ${INSTALL_INCLUDE_DIR}/core)
install(FILES ${netatmoapi_model_HDRS} DESTINATION ${INSTALL_INCLUDE_DIR}/model)
install(FILES ${netatmoapi_exceptions_HDRS} DESTINATION ${INSTALL_INCLUDE_DIR}/exceptions)
