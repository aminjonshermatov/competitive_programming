//
// Created by aminjon on 1/29/24.
//
#include <bits/stdc++.h>

template <typename T, std::size_t N>
class SquareMatrix {
 public:
  constexpr static SquareMatrix I() {
    SquareMatrix<T, N> ret{};
    for (std::size_t i = 0u; i < N; ++i) {
      ret(i, i) = T{1};
    }
    return ret;
  }

  constexpr T& operator()(int i, int j) noexcept {
    return Data_[i * N + j];
  }
  [[nodiscard]] constexpr T operator()(int i, int j) const noexcept {
    return Data_[i * N + j];
  }

  constexpr SquareMatrix operator*(const SquareMatrix& other) noexcept {
    SquareMatrix mat{};
    for (std::size_t i = 0u; i < N; ++i) {
      for (std::size_t j = 0u; j < N; ++j) {
        for (std::size_t k = 0u; k < N; ++k) {
          mat(i, j) += operator()(i, k) * other(k, j);
        }
      }
    }
    return mat;
  }

  constexpr SquareMatrix Pow(uint64_t n) const noexcept {
    auto ret = SquareMatrix::I();
    auto cur = *this;
    for (; n > 0; n >>= 1, cur = cur * cur) {
      if (n % 2 == 1) {
        ret = ret * cur;
      }
    }
    return ret;
  }

  template <typename U, std::size_t M>
  friend std::ostream& operator<<(std::ostream& os, const SquareMatrix<U, M>& mat) {
    for (std::size_t i = 0u; i < M; ++i) {
      for (std::size_t j = 0u; j < M; ++j) {
        os << mat(i, j) << ' ';
      }
      os << '\n';
    }
    return os;
  }

 private:
  std::array<T, N * N> Data_{};
};