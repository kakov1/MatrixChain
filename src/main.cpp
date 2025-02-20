#include "matrix_chain.hpp"

using namespace hwm;

int main() {
  // MatrixChain<int> chain;
  // 5, 30, 35, 15, 5, 10
  // 10, 30, 5, 60
  //  60,10, 5, 1, 2, 4, 30, 10, 100, 1500, 121, 241, 5, 30, 10, 11
  // ans: ((A1 * (A2 * A3)) * (((((((((((A4 * A5) * A6) * A7) * A8) * A9) * A10)
  // * A11) * A12) * A13) * A14) * A15))

  // std::vector<size_t> test = {60,  10,   5,   1,   2, 4,  30, 10,
  // 100, 1500, 121, 241, 5, 30, 10, 11};
  // std::vector<size_t> test = {10, 30, 5, 60};

  std::vector<size_t> a;
  size_t buf;

  while (std::cin >> buf) {
    a.push_back(buf);
  }

  std::vector<size_t> ans = MatrixChain<int>::optimal_order(a);

  std::cout << std::endl;
  for (auto &&mtrx : ans) {
    std::cout << mtrx << " ";
  }

  std::cout << std::endl;
}