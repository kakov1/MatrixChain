cmake_minimum_required(VERSION 3.14)
project(MatrixChain)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

include(FetchContent)

FetchContent_Declare(
  matrix
  GIT_REPOSITORY https://github.com/kakov1/Matrix.git
  GIT_TAG        9760458fc97e01f069879e1a812187788723e1e9
)

FetchContent_MakeAvailable(matrix)

find_package(GTest REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(benchmark)

