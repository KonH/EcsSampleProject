cmake_minimum_required(VERSION 3.29)
project(EcsSampleProject)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/WX)
endif()

# Rendering options
option(USE_RENDER_RAYLIB "Use Raylib for rendering" ON)

# Logging options
option(USE_LOG_COUT "Use standard output for logging" ON)

FetchContent_Declare(
        EnTT
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG v3.13.2
)
FetchContent_MakeAvailable(EnTT)

FetchContent_Declare(
        tweeny
        GIT_REPOSITORY https://github.com/mobius3/tweeny.git
        GIT_TAG v3.2.0
)
FetchContent_MakeAvailable(tweeny)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG c19cfee61e136effb05a7fc8a037b0db3b13bd4c
)
FetchContent_MakeAvailable(benchmark)

# Source files
file(GLOB_RECURSE SRC_FILES
        ${CMAKE_SOURCE_DIR}/src/Components/*.h
        ${CMAKE_SOURCE_DIR}/src/Execution/*.h
        ${CMAKE_SOURCE_DIR}/src/Execution/*.cpp
        ${CMAKE_SOURCE_DIR}/src/Logging/*.h
        ${CMAKE_SOURCE_DIR}/src/Logging/*.cpp
        ${CMAKE_SOURCE_DIR}/src/Execution/*.cpp
        ${CMAKE_SOURCE_DIR}/src/Systems/*.cpp
        ${CMAKE_SOURCE_DIR}/src/Types/*.h
        ${CMAKE_SOURCE_DIR}/src/Utils/*.h
)

file(GLOB_RECURSE FRONTEND_SRC_FILES
        ${CMAKE_SOURCE_DIR}/src/Frontend/*.h
        ${CMAKE_SOURCE_DIR}/src/Frontend/*.cpp
)

# Main project executable
add_executable(EcsSampleProject ${CMAKE_SOURCE_DIR}/src/main.cpp ${SRC_FILES} ${FRONTEND_SRC_FILES})
target_link_libraries(EcsSampleProject EnTT tweeny)

if(USE_RENDER_RAYLIB)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 5.0
    )
    FetchContent_MakeAvailable(raylib)
    target_include_directories(EcsSampleProject PRIVATE ${raylib_SOURCE_DIR}/src)
    target_link_libraries(EcsSampleProject raylib)
    target_compile_definitions(EcsSampleProject PRIVATE USE_RENDER_RAYLIB)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_precompile_headers(EcsSampleProject PRIVATE src/pch.h)
endif()

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

if(USE_RENDER_RAYLIB)
    target_include_directories(EcsSampleProject
            PRIVATE ${CMAKE_SOURCE_DIR}/src
            SYSTEM ext/raylib/src
    )
    target_link_libraries(EcsSampleProject raylib)
    target_compile_definitions(EcsSampleProject PRIVATE USE_RENDER_RAYLIB)
endif()

if (USE_LOG_COUT)
    target_compile_definitions(EcsSampleProject PRIVATE USE_LOG_COUT)
endif()

enable_testing()

include(GoogleTest)

# Tests executable
add_executable(runTests tests/test_main.cpp ${SRC_FILES})
target_link_libraries(runTests gtest gtest_main EnTT tweeny)
target_include_directories(runTests
        PRIVATE ${CMAKE_SOURCE_DIR}/src)
gtest_discover_tests(runTests)

# Benchmarks executable
add_executable(runBenchmarks benchmarks/benchmark_main.cpp)
target_link_libraries(runBenchmarks benchmark EnTT)
