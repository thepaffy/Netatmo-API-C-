enable_testing()
find_package(GTest REQUIRED)

add_subdirectory(unitTests)
add_subdirectory(integrationTests)
