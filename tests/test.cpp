#include "matrix_chain.hpp"
#include <cstddef>
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace hwm;
using std::size_t;

const std::string TEST_DIR = std::string(TEST_DATA_DIR) + "/";

class EteTests : public testing::Test {
protected:
  std::vector<size_t> test(size_t test_number) {
    std::ifstream test_file(TEST_DIR + "in/" + std::to_string(test_number) +
                            "test.in");

    test_file.exceptions(std::ifstream::badbit);

    std::vector<size_t> sizes;
    long long number, buf;

    test_file >> number;

    for (; number > 0; --number) {
      test_file >> buf;

      sizes.push_back(buf);
    }

    std::vector<size_t> ans = MatrixChain<long long>::find_optimal_order(sizes);

    return ans;
  }

  std::vector<size_t> get_answer(size_t test_number) {
    std::ifstream answer_file(TEST_DIR + "out/" + std::to_string(test_number) +
                              "test.out");

    answer_file.exceptions(std::ifstream::badbit);

    size_t buf;
    std::vector<size_t> ans;

    while (answer_file >> buf) {
      ans.push_back(buf);
    }

    return ans;
  }
};

TEST_F(EteTests, test) {
  for (int i = 1; i <= 5; ++i)
    ASSERT_TRUE(test(i) == get_answer(i));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
