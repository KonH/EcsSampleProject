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
# TODO - remove legacy options
option(USE_RENDER_SFML "Use SFML for rendering" OFF) # Legacy option
option(USE_RENDER_SDL "Use SDL2 for rendering" OFF) # Legacy option
option(USE_RENDER_RAYLIB "Use Raylib for rendering" ON)

# Logging options
option(USE_LOG_COUT "Use standard output for logging" ON)
option(USE_LOG_SDL "Use SDL2 for logging" OFF) # Legacy option

# TODO - update / downgrade dependencies to stable versions

FetchContent_Declare(
        EnTT
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG 1ddc887ac43f6ba0ae5d39c14ec08ef7fcb0b435
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
        GIT_TAG 9ff2450a56aed4f7f124f5104d9e3088bf791ee9
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG 64b5d8cd111721e4e3e0174825b04eb95309df96
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

if(USE_RENDER_SFML)
    FetchContent_Declare(
            SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 7083b6562e08c48c3cf3303bc69b9037c321d806
    )
    FetchContent_MakeAvailable(SFML)
    target_link_libraries(EcsSampleProject sfml-system sfml-window sfml-graphics)
    target_include_directories(EcsSampleProject PRIVATE ${SFML_SOURCE_DIR}/include)
    target_compile_definitions(EcsSampleProject PRIVATE USE_RENDER_SFML)
endif()

if(USE_RENDER_SDL)
    FetchContent_Declare(
            SDL
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG SDL2
    )
    FetchContent_MakeAvailable(SDL)
    target_include_directories(EcsSampleProject PRIVATE ${SDL_SOURCE_DIR}/include)
    target_link_libraries(EcsSampleProject SDL2)
    target_compile_definitions(EcsSampleProject PRIVATE USE_RENDER_SDL)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_precompile_headers(EcsSampleProject PRIVATE src/pch.h)
endif()

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

if(USE_RENDER_SFML)
    set(BUILD_SHARED_LIBS FALSE)
    target_link_libraries(EcsSampleProject sfml-system sfml-window sfml-graphics)
    target_include_directories(EcsSampleProject
            PRIVATE ${CMAKE_SOURCE_DIR}/src
            SYSTEM ext/SFML/include
    )
    target_compile_definitions(EcsSampleProject PRIVATE USE_RENDER_SFML)
elseif(USE_RENDER_SDL)
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
