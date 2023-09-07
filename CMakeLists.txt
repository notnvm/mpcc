cmake_minimum_required(VERSION 3.18)

project(mpcc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED YES)

# set(CMAKE_BUILD_TYPE Release)

set(UTILS src/generator.cpp src/lib.cpp)
set(EXE src/main.cpp ${UTILS})
set(BENCH bench/bench.cpp ${UTILS})

# add_library(mpcclib STATIC include/generator.h src/generator.cpp)
# target_include_directories(mpcclib PRIVATE include)

add_executable(out ${EXE})
target_include_directories(out PRIVATE include)

# target_link_libraries(out PRIVATE mpcclib)

# from google docs
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG main) # need main for benchmark::benchmark

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(
  googletest
  googlebenchmark)

add_executable(g_bench ${BENCH})
target_include_directories(g_bench PRIVATE include)
target_link_libraries(g_bench benchmark::benchmark)

enable_testing()

add_executable(
  test_out
  tests/tests.cpp
  src/generator.cpp
  src/lib.cpp
)
target_link_libraries(
  test_out
  GTest::gtest_main
)
target_include_directories(test_out PRIVATE include)

include(GoogleTest)
gtest_discover_tests(test_out)