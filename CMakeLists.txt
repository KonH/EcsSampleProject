cmake_minimum_required(VERSION 3.29)
project(EcsSampleProject)

set(CMAKE_CXX_STANDARD 20)

option(USE_RENDER_SFML "Use SFML for rendering" ON)
option(USE_RENDER_SDL "Use SDL for rendering" OFF)

add_subdirectory(ext/entt)

file(GLOB_RECURSE SRC_FILES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/Components/*.h
        ${CMAKE_SOURCE_DIR}/src/Systems/*.cpp
        ${CMAKE_SOURCE_DIR}/src/Types/*.h
)

# Main project executable
add_executable(EcsSampleProject ${SRC_FILES})
target_link_libraries(EcsSampleProject EnTT)

if(USE_RENDER_SFML)
    set(BUILD_SHARED_LIBS FALSE)
    add_subdirectory(ext/SFML)
    target_link_libraries(EcsSampleProject sfml-system sfml-window sfml-graphics)
    target_include_directories(EcsSampleProject
            PRIVATE ${CMAKE_SOURCE_DIR}/src
            SYSTEM ext/SFML/include)
    target_compile_definitions(EcsSampleProject PRIVATE USE_RENDER_SFML)
elseif(USE_RENDER_SDL)
    add_subdirectory(ext/SDL)
    target_link_libraries(EcsSampleProject SDL3::SDL3)
    target_include_directories(EcsSampleProject
            PRIVATE ${CMAKE_SOURCE_DIR}/src
            SYSTEM ext/SDL/include/SDL3)
    target_compile_definitions(EcsSampleProject PRIVATE USE_RENDER_SDL)
    add_custom_command(TARGET EcsSampleProject POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3::SDL3>
            $<TARGET_FILE_DIR:EcsSampleProject>)
else()
    message(FATAL_ERROR "Either USE_SFML or USE_SDL must be enabled.")
endif()

enable_testing()
add_subdirectory(ext/googletest)

add_subdirectory(ext/benchmark)

include(GoogleTest)

# Tests executable
add_executable(runTests tests/test_main.cpp)
target_link_libraries(runTests gtest gtest_main)
gtest_discover_tests(runTests)

# Benchmarks executable
add_executable(runBenchmarks benchmarks/benchmark_main.cpp)
target_link_libraries(runBenchmarks benchmark EnTT)