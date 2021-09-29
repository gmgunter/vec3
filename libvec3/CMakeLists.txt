cmake_minimum_required(VERSION 3.20)

# Fetch version info from the top-level text file.
file(STRINGS "../VERSION" version)

project(
    vec3
    VERSION ${version}
    LANGUAGES C CXX)

# Check if this is the main (top-level) CMake project or was included as a
# sub-project.
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(main_project ON)
else()
    set(main_project OFF)
endif()

option(VEC3_INSTALL "Enable library installation" ${main_project})
option(VEC3_TEST "Enable test suite" ${main_project})

add_subdirectory(src lib)

if(VEC3_TEST)
    include(CTest)
    add_subdirectory(test)
endif()
