add_executable(test_chain test.cpp)

file(COPY ${CMAKE_SOURCE_DIR}/tests/in/
          ${CMAKE_SOURCE_DIR}/tests/out/
     DESTINATION ${CMAKE_BINARY_DIR}/tests/)

target_include_directories(test_chain PUBLIC ${CMAKE_SOURCE_DIR}/inc)

target_link_libraries(test_chain PRIVATE matrix gtest::gtest) 
