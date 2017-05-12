cmake_minimum_required(VERSION 3.1.0)

project(netatmoapi++)

add_subdirectory(src)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})
if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    set(doxyfile_src ${CMAKE_CURRENT_SOURCE_DIR}/netatmoapi++.doxy)
    set(doxyfile_dst ${CMAKE_CURRENT_BINARY_DIR}/doc/netatmoapi++.doxy)
    set(doxygen_error ${CMAKE_CURRENT_BINARY_DIR}/doc/doxygen.err)

    configure_file(${doxyfile_src} ${doxyfile_dst} @ONLY)

    add_custom_target(docs
        COMMAND "INPUT_DIRECTORY=${CMAKE_CURRENT_SOURCE_DIR}" ${DOXYGEN_EXECUTABLE} ${doxyfile_src} 2> ${doxygen_error}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/netatmo++-html DESTINATION doc OPTIONAL)
    install(FILES ${doxygen_error} DESTINATION doc OPTIONAL)

endif()

