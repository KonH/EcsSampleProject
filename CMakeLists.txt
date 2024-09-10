cmake_minimum_required(VERSION 3.29)
project(EcsSampleProject)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(ext/entt)

set(BUILD_SHARED_LIBS FALSE)
add_subdirectory(ext/SFML)

enable_testing()
add_subdirectory(ext/googletest)

add_subdirectory(ext/benchmark)

include(GoogleTest)

file(GLOB_RECURSE SRC_FILES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/Components/*.h
        ${CMAKE_SOURCE_DIR}/src/Systems/*.cpp
)

# Main project executable
add_executable(EcsSampleProject ${SRC_FILES})
target_link_libraries(EcsSampleProject sfml-system sfml-window sfml-graphics EnTT)
target_include_directories(EcsSampleProject
        PRIVATE ${CMAKE_SOURCE_DIR}/src
        SYSTEM ext/SFML/include
        SYSTEM ext/entt/src)

# Tests executable
add_executable(runTests tests/test_main.cpp)
target_link_libraries(runTests gtest gtest_main)
gtest_discover_tests(runTests)

# Benchmarks executable
add_executable(runBenchmarks benchmarks/benchmark_main.cpp)
target_link_libraries(runBenchmarks benchmark EnTT)