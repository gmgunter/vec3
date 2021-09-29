include(GNUInstallDirs)

add_library(vec3)
add_library(vec3::vec3 ALIAS vec3)

# Require C++17 minimum standard.
target_compile_features(vec3 PUBLIC cxx_std_17)

target_sources(vec3 PRIVATE # cmake-format: sortable
                            vec3/vec3.cpp)

target_include_directories(
    vec3 PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
                $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_target_properties(vec3 PROPERTIES VERSION ${PROJECT_VERSION}
                                      SOVERSION ${PROJECT_VERSION_MAJOR})

if(NOT VEC3_INSTALL)
    return()
endif()

# Install public header files.
install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/vec3
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING
    PATTERN *.hpp)

# Install static/shared library.
install(
    TARGETS vec3
    EXPORT vec3Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

# Export CMake target definitions.
install(
    EXPORT vec3Targets
    NAMESPACE vec3::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/vec3)

# Generate CMake package config files.
include(CMakePackageConfigHelpers)
set(build_config_file ${CMAKE_CURRENT_BINARY_DIR}/cmake/vec3/vec3Config.cmake)
set(build_config_version_file
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/vec3/vec3ConfigVersion.cmake)
configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/vec3Config.cmake.in ${build_config_file}
    INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/vec3)

# ---TODO---
# Prior to v1.0.0, each minor release is expected to be breaking. Change
# `COMPATIBILITY` to `SameMajorVersion` at v1.0.0.
write_basic_package_version_file(
    ${build_config_version_file}
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMinorVersion)

# Install CMake package config files.
install(FILES ${build_config_file} ${build_config_version_file}
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR})
