set(CMAKE_C_COMPILER "/usr/bin/gcc-10")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-10")
cmake_minimum_required(VERSION 3.20)

project(wtlib_examples LANGUAGES CXX)

find_package(WTLIB REQUIRED PATHS "${PROJECT_SOURCE_DIR}/../lib/cmake")

add_executable(example_image imageread.cpp)

target_link_libraries(example_image PRIVATE wtlib::sources)

target_compile_definitions(example_image PRIVATE RESOURCE_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/resources\")

add_executable(example_sequence sequenceread.cpp)

target_link_libraries(example_sequence PRIVATE wtlib::sources)

target_compile_definitions(example_sequence PRIVATE RESOURCE_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/resources\")
