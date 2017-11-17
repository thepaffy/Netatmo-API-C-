cmake_minimum_required(VERSION 3.5.0)

enable_testing()
find_package(GTest REQUIRED)

add_subdirectory(unitTests)
add_subdirectory(integrationTests)
