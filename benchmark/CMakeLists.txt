add_executable(benchmark benchmark.cpp)

set(BENCHMARK_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(benchmark PUBLIC BENCHMARK_DATA_DIR="${BENCHMARK_DATA_DIR}")

target_include_directories(benchmark PUBLIC ${CMAKE_SOURCE_DIR}/inc)

target_link_libraries(benchmark PRIVATE matrix) 