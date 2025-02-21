add_executable(benchmark benchmark.cpp)

file(COPY ${CMAKE_SOURCE_DIR}/benchmark/in/
          ${CMAKE_SOURCE_DIR}/benchmark/out/
     DESTINATION ${CMAKE_BINARY_DIR}/benchmark/)

target_include_directories(benchmark PUBLIC ${CMAKE_SOURCE_DIR}/inc)

target_link_libraries(benchmark PRIVATE matrix) 