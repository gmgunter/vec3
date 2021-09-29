find_package(Catch2 REQUIRED CONFIG)

add_executable(vec3-test # cmake-format: sortable
               main.cpp vec3_test.cpp)

target_link_libraries(vec3-test PRIVATE vec3::vec3 Catch2::Catch2)

include(Catch)
catch_discover_tests(vec3-test)
