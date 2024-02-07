cmake_minimum_required(VERSION 3.18)

project(mpcc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED YES)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(UTILS src/utils/generator.cpp src/lib/lib.cpp)
set(EXE src/main.cpp ${UTILS})
set(BENCH src/bench/bench.cpp ${UTILS})

add_executable(mpcc_bin ${EXE})
target_include_directories(mpcc_bin PRIVATE include)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG main
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(
  googletest
  googlebenchmark
)

add_executable(mpcc_bench ${BENCH})
target_include_directories(mpcc_bench PRIVATE include)
target_link_libraries(mpcc_bench benchmark::benchmark)

enable_testing()

add_executable(
  mpcc_tests
  src/tests/tests.cpp
  src/utils/generator.cpp
  src/lib/lib.cpp
)
target_link_libraries(
  mpcc_tests
  GTest::gtest_main
)
target_include_directories(mpcc_tests PRIVATE include)

include(GoogleTest)
gtest_discover_tests(mpcc_tests)