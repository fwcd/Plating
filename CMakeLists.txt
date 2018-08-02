cmake_minimum_required(VERSION 2.6)
project(Plating)

add_subdirectory(src)

add_executable(PlatingTest src/test/tests.c)
target_link_libraries(PlatingTest Plating)
target_link_libraries(PlatingTest PlatingTests)
set_target_properties(PlatingTest PROPERTIES OUTPUT_NAME "platingtest")

target_include_directories(Plating PUBLIC include)
target_include_directories(PlatingTests PRIVATE include)
