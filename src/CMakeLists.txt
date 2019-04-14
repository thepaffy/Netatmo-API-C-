include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(${PROJECT_NAME}_VERSION_MAJOR 2)
set(${PROJECT_NAME}_VERSION_STRING ${${PROJECT_NAME}_VERSION_MAJOR})
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set(netatmoapi_SRCS
    core/naclient.cpp
    core/nawsapi.cpp
    core/parsing.cpp
    core/utils.cpp
    model/station.cpp
    model/module.cpp
    model/measures.cpp
    model/place.cpp
    exceptions/curlexception.cpp
    exceptions/naapiexception.cpp
)

set(netatmoapi_core_HDRS
    core/naclient.h
    core/nawsapi.h
    core/parsing.h
)

set(netatmoapi_core_private_HDRS
    core/private/parsing_p.h
    core/private/scopeexit.h
    core/private/utils.h
)

set(netatmoapi_model_HDRS
    model/station.h
    model/module.h
    model/measures.h
    model/params.h
    model/place.h
)

set(netatmoapi_exceptions_HDRS
    exceptions/curlexception.h
    exceptions/naapiexception.h
)

add_library(${PROJECT_NAME} SHARED ${netatmoapi_SRCS} ${netatmoapi_core_HDRS} ${netatmoapi_core_private_HDRS} ${netatmoapi_model_HDRS} ${netatmoapi_exceptions_HDRS})
generate_export_header(${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${${PROJECT_NAME}_VERSION_STRING} SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR})
target_link_libraries(${PROJECT_NAME} PRIVATE curl)

install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_LIB_DIR})
install(FILES ${netatmoapi_core_HDRS} DESTINATION ${INSTALL_INCLUDE_DIR}/core)
install(FILES ${netatmoapi_model_HDRS} DESTINATION ${INSTALL_INCLUDE_DIR}/model)
install(FILES ${netatmoapi_exceptions_HDRS} DESTINATION ${INSTALL_INCLUDE_DIR}/exceptions)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_export.h DESTINATION ${INSTALL_INCLUDE_DIR})
