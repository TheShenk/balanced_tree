cmake_minimum_required(VERSION 3.26)
project(balanced_tree)

set(CMAKE_CXX_STANDARD 20)

add_executable(balanced_tree main.cpp tree.h)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(balanced_tree_test test.cpp tree.h)
target_link_libraries(balanced_tree_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(balanced_tree_test)