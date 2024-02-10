cmake_minimum_required(VERSION 3.18)

project(mpcc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED YES)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CPP src/utils/generator.cpp src/lib/lib.cpp src/solver/solver.cpp)
set(EXE src/main.cpp ${CPP})
set(BENCH src/bench/bench.cpp ${CPP})
set(TESTS src/tests/tests.cpp src/utils/generator.cpp src/lib/lib.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        main
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(
  googletest
  googlebenchmark
)

#mpcc
# add_subdirectory(old/vendor/or-tools)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/ortools)
find_package(ortools CONFIG REQUIRED)
add_executable(mpcc_bin ${EXE})
target_link_libraries(
  mpcc_bin 
  ortools::ortools
)

#bench
add_executable(mpcc_bench ${BENCH})
target_link_libraries(
  mpcc_bench 
  benchmark::benchmark
  ortools::ortools
)

#tests
enable_testing()
add_executable(mpcc_tests ${TESTS})
target_link_libraries(
  mpcc_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(mpcc_tests)