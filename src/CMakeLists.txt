add_executable(matrixchain main.cpp)

target_include_directories(matrixchain PUBLIC ${CMAKE_SOURCE_DIR}/inc/)

target_link_libraries(matrixchain PRIVATE matrix) 
