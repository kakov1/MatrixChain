cmake_minimum_required(VERSION 3.14)
project(MatrixChain)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
include(CTest)

FetchContent_Declare(
  matrix
  GIT_REPOSITORY https://github.com/kakov1/Matrix.git
  GIT_TAG        4ea5dc83e1c44f62c4fd6757465fb06a7367ee7f
)

FetchContent_MakeAvailable(matrix)

find_package(GTest REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(benchmark)

