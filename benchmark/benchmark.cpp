#include "matrix_chain.hpp"
#include <chrono>
#include <fstream>

using namespace hwm;

const std::string BENCHMARK_DIR = std::string(BENCHMARK_DATA_DIR) + "/";

template <typename T>
void create_chain_from_file(std::string file_path, MatrixChain<T> &chain) {
  std::ifstream benchmark_file(file_path);

  std::size_t x, y, mtrx_num;
  int buf;
  std::vector<T> numbers;

  benchmark_file >> mtrx_num;

  for (int i = 0; i < mtrx_num; ++i) {
    benchmark_file >> x >> y;

    for (int j = 0; j < x * y; ++j) {
      benchmark_file >> buf;
      numbers.push_back(buf);
    }

    chain.emplace_back(x, y, numbers.begin(), numbers.end());
  }
}

int main() {
  MatrixChain<long long> chain;

  create_chain_from_file(BENCHMARK_DIR + "in/" + "benchmark.in", chain);

  auto start_opt = std::chrono::high_resolution_clock::now();
  Matrix<long long> optimal_res = chain.optimal_multiply();
  auto end_opt = std::chrono::high_resolution_clock::now();

  auto start_naive = std::chrono::high_resolution_clock::now();
  Matrix<long long> naive_res = chain.naive_multiply();
  auto end_naive = std::chrono::high_resolution_clock::now();

  auto opt_duration = std::chrono::duration_cast<std::chrono::microseconds>(
      end_opt - start_opt);
  auto naive_duration = std::chrono::duration_cast<std::chrono::microseconds>(
      end_naive - start_naive);

  std::cout << opt_duration.count() << std::endl;
  std::cout << naive_duration.count() << std::endl;
}