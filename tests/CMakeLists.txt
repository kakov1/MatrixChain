add_executable(test_chain test.cpp)

include(CTest)

set(TEST_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(test_chain PUBLIC TEST_DATA_DIR="${TEST_DATA_DIR}")
target_include_directories(test_chain PUBLIC ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(test_chain PRIVATE matrix GTest::gtest) 

gtest_discover_tests(test_chain)
