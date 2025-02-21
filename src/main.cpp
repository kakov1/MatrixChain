#include "matrix_chain.hpp"

using namespace hwm;

int main() {
  std::vector<size_t> sizes;
  long long number, buf;

  std::cin >> number;

  if (!std::cin.good() || number <= 0) {
    throw std::runtime_error(
        "Number of sizes must be unsigned int and not zero.");
  }

  for (; number > 0; --number) {
    std::cin >> buf;

    if (!std::cin.good() || buf <= 0) {
      throw std::runtime_error("Input error.");
    }

    sizes.push_back(buf);
  }

  std::vector<size_t> ans = MatrixChain<long long>::find_optimal_order(sizes);

  for (auto &&mtrx : ans) {
    std::cout << mtrx << " ";
  }

  std::cout << std::endl;
}
