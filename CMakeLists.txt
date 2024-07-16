cmake_minimum_required(VERSION 3.29)
project(EcsSampleProject)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(ext/entt)

set(BUILD_SHARED_LIBS FALSE)
add_subdirectory(ext/SFML)

enable_testing()
add_subdirectory(ext/googletest)

include(GoogleTest)

add_executable(EcsSampleProject src/main.cpp)

target_link_libraries(EcsSampleProject sfml-system sfml-window sfml-graphics EnTT)

target_include_directories(EcsSampleProject PRIVATE ext/SFML/include ext/entt/src)

add_executable(runTests tests/test_main.cpp)
target_link_libraries(runTests gtest gtest_main)
gtest_discover_tests(runTests)