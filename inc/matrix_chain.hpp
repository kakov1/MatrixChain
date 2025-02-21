#pragma once

#include "matrix.hpp"
#include <algorithm>
#include <climits>
#include <ranges>
#include <stack>
#include <unordered_map>
#include <vector>

namespace hwm {
template <typename T> class MatrixChain final {
private:
  using size_t = std::size_t;
  using size_vector = std::vector<size_t>;
  using order_table = std::unordered_map<size_t, std::vector<size_t>>;
  using subchains_info = std::vector<std::vector<size_t>>;
  using reference = T &;
  using const_reference = const T &;

private:
  std::vector<Matrix<T>> chain_;

  void validate_next_matrix_size(const Matrix<T> &mtrx) const {
    if (!chain_.empty() && chain_.back().get_cols() != mtrx.get_rows()) {
      throw std::runtime_error("Incorrect size for multiply.");
    }
  }

  void validate_prev_matrix_size(const Matrix<T> &mtrx) const {
    if (!chain_.empty() && chain_.front().get_rows() != mtrx.get_cols()) {
      throw std::runtime_error("Incorrect size for multiply.");
    }
  }

  void validate_chain_size() const {
    if (chain_.size() == 0) {
      throw std::runtime_error("Chain is empty.");
    }
  }

  void validate_correct_pos(size_t pos) const {
    if (!(pos >= 0 && pos < chain_.size())) {
      throw std::runtime_error("Incorrect position.");
    }
  }

  static void get_optimal_order(size_t brace_count, order_table &open,
                                const subchains_info &split, size_t i,
                                size_t j) {
    struct StackFrame {
      size_t i;
      size_t j;
      bool visited;
    };

    std::stack<StackFrame> stack;
    stack.push({i, j, false});

    while (!stack.empty()) {
      auto &frame = stack.top();
      size_t current_i = frame.i;
      size_t current_j = frame.j;

      if (current_i == current_j) {
        stack.pop();
        continue;
      }

      if (!frame.visited) {
        size_t k = split[current_i][current_j];
        open[++brace_count].push_back(k);

        frame.visited = true;
        stack.push({current_i, k, false});
        stack.push({k + 1, current_j, false});
      } else {
        stack.pop();
      }
    }
  }

  static void print_optimal_order(const subchains_info &split, size_t i,
                                  size_t j) {
    if (i == j) {
      std::cout << i;
    } else {
      std::cout << "(";
      print_optimal_order(split, i, split[i][j]);
      std::cout << " * ";
      print_optimal_order(split, split[i][j] + 1, j);
      std::cout << ")";
    }
  }

public:
  MatrixChain() {}

  reference front() {
    validate_chain_size();

    return chain_.front();
  }

  const_reference front() const {
    validate_chain_size();

    return chain_.front();
  }

  reference back() {
    validate_chain_size();

    return chain_.back();
  }

  const_reference back() const {
    validate_chain_size();

    return chain_.back();
  }

  reference operator[](size_t pos) {
    validate_correct_pos(pos);

    return chain_[pos];
  }

  const_reference operator[](size_t pos) const {
    validate_correct_pos(pos);

    return chain_[pos];
  }

  void push_back(const Matrix<T> &mtrx) {
    validate_next_matrix_size(mtrx);

    chain_.push_back(mtrx);
  }

  void push_front(const Matrix<T> &mtrx) {
    validate_prev_matrix_size(mtrx);

    chain_.push_back(mtrx);
  }

  void pop_back() {
    validate_chain_size();

    chain_.pop_back();
  }

  template <typename... Args> void emplace_back(Args &&...args) {
    Matrix<T> tmp(std::forward<Args>(args)...);

    validate_next_matrix_size(tmp);

    chain_.emplace_back(std::move(tmp));
  }

  template <typename... Args> void emplace_front(Args &&...args) {
    Matrix<T> tmp(std::forward<Args>(args)...);

    validate_prev_matrix_size(tmp);

    chain_.emplace_front(std::move(tmp));
  }

  Matrix<T> naive_multiply() const {
    validate_chain_size();

    Matrix<T> result = chain_[0];

    for (auto &&mtrx : std::views::drop(chain_, 1)) {
      result = result.multiply(mtrx);
    }

    return result;
  }

  Matrix<T> optimal_multiply() const {
    validate_chain_size();

    auto chain = chain_;
    size_vector optimal_order = find_optimal_order();
    
    std::vector<int> mtrcs_positions(optimal_order.size() + 1, 1);
    size_t left = 0, right = 0;

    for (auto &&mtrx : optimal_order) {
      left = mtrx;
      right = mtrx + 1;

      if (mtrcs_positions[left] == 0) {
        while (mtrcs_positions[left] == 0) {
          --left;
        }
      }

      if (mtrcs_positions[right] == 0) {
        while (mtrcs_positions[right] == 0) {
          ++right;
        }
      }

      chain[left] = chain[left].multiply(chain[right]);
      mtrcs_positions[right] = 0;
    }

    return chain[0];
  }

  size_vector find_optimal_order() const {
    size_vector sizes;

    sizes.push_back(chain_.front().get_rows());

    for (auto &&mtrx : chain_) {
      sizes.push_back(mtrx.get_cols());
    }

    return find_optimal_order(sizes);
  }

  static size_vector find_optimal_order(const size_vector &sizes) {
    size_t n = sizes.size() - 1;
    subchains_info costs(n, size_vector(n, 0));
    subchains_info split(n, size_vector(n, 0));

    for (size_t i = 0; i < n; ++i) {
      costs[i][i] = 0;
    }

    for (size_t length = 2; length <= n; ++length) {
      for (size_t i = 0; i < n - length + 1; ++i) {
        size_t j = i + length - 1;
        costs[i][j] = UINT_MAX;

        for (size_t k = i; k < j; ++k) {
          size_t cost = costs[i][k] + costs[k + 1][j] +
                        sizes[i] * sizes[k + 1] * sizes[j + 1];

          if (cost < costs[i][j]) {
            costs[i][j] = cost;
            split[i][j] = k;
          }
        }
      }
    }

#ifdef DEBUG
    print_optimal_order(split, 0, n - 1);
    std::cout << std::endl;
#endif

    order_table open{};
    get_optimal_order(0, open, split, 0, n - 1);

    size_vector keys, ans;

    for (auto &&pair : open) {
      keys.push_back(pair.first);
    }

    std::sort(keys.begin(), keys.end(), std::greater<size_t>());

    for (auto &&key : keys) {
      for (auto &&mtrx : open[key]) {
        ans.push_back(mtrx);
      }
    }

    return ans;
  }

  void print_info(const subchains_info &&vect) {
    for (auto &&i : vect) {
      std::cout << "[ ";
      for (auto it = i.begin(); it != i.end(); ++it) {
        std::cout << *it;
        if (std::next(it) != i.end()) {
          std::cout << ", ";
        }
      }
      std::cout << " ]" << std::endl;
    }
  }
};
} // namespace hwm
