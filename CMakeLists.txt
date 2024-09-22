cmake_minimum_required(VERSION 3.29)
project(EcsSampleProject)

set(CMAKE_CXX_STANDARD 20)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/WX)
    target_precompile_headers(EcsSampleProject PRIVATE src/pch.h)
endif()

# Rendering options
option(USE_RENDER_SFML "Use SFML for rendering" OFF) # Legacy option
option(USE_RENDER_SDL "Use SDL2 for rendering" OFF) # Legacy option
option(USE_RENDER_RAYLIB "Use Raylib for rendering" ON)

# Logging options
option(USE_LOG_COUT "Use standard output for logging" ON)
option(USE_LOG_SDL "Use SDL2 for logging" OFF) # Legacy option

add_subdirectory(ext/entt)
add_subdirectory(ext/tweeny)

# Source files
file(GLOB_RECURSE SRC_FILES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/Components/*.h
        ${CMAKE_SOURCE_DIR}/src/Execution/*.h
        ${CMAKE_SOURCE_DIR}/src/Execution/*.cpp
        ${CMAKE_SOURCE_DIR}/src/Frontend/*.h
        ${CMAKE_SOURCE_DIR}/src/Frontend/*.cpp
        ${CMAKE_SOURCE_DIR}/src/Logger/*.h
        ${CMAKE_SOURCE_DIR}/src/Logger/*.cpp
        ${CMAKE_SOURCE_DIR}/src/Execution/*.cpp
        ${CMAKE_SOURCE_DIR}/src/Systems/*.cpp
        ${CMAKE_SOURCE_DIR}/src/Types/*.h
)

# Main project executable
add_executable(EcsSampleProject ${SRC_FILES})
target_link_libraries(EcsSampleProject EnTT tweeny)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

if(USE_RENDER_SFML)
    set(BUILD_SHARED_LIBS FALSE)
    add_subdirectory(ext/SFML)
    target_link_libraries(EcsSampleProject sfml-system sfml-window sfml-graphics)
    target_include_directories(EcsSampleProject
            PRIVATE ${CMAKE_SOURCE_DIR}/src
            SYSTEM ext/SFML/include
    )
    target_compile_definitions(EcsSampleProject PRIVATE USE_RENDER_SFML)
elseif(USE_RENDER_SDL)
    add_subdirectory(ext/SDL)
    target_include_directories(EcsSampleProject
            PRIVATE ${CMAKE_SOURCE_DIR}/src
            SYSTEM ext/SDL/include
    )
    target_link_libraries(EcsSampleProject SDL2)
    target_compile_definitions(EcsSampleProject PRIVATE USE_RENDER_SDL)
    add_custom_command(TARGET EcsSampleProject POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE_DIR:EcsSampleProject>/ext/SDL/SDL2d.dll
            $<TARGET_FILE_DIR:EcsSampleProject>
    )
elseif(USE_RENDER_RAYLIB)
    add_subdirectory(ext/raylib)
    target_include_directories(EcsSampleProject
            PRIVATE ${CMAKE_SOURCE_DIR}/src
            SYSTEM ext/raylib/src
    )
    target_link_libraries(EcsSampleProject raylib)
    target_compile_definitions(EcsSampleProject PRIVATE USE_RENDER_RAYLIB)
else()
    message(FATAL_ERROR "Some render option must be enabled.")
endif()

if (USE_LOG_COUT)
    target_compile_definitions(EcsSampleProject PRIVATE USE_LOG_COUT)
endif()

if (USE_LOG_SDL)
    target_compile_definitions(EcsSampleProject PRIVATE USE_LOG_SDL)
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
