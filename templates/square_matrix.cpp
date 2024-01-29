//
// Created by aminjon on 1/29/24.
//
#include <bits/stdc++.h>

template <typename T, std::size_t N> class SquareMatrix {
  std::array<T, N * N> data{};
public:
  constexpr static SquareMatrix id() {
    SquareMatrix<T, N> ret{};
    for (std::size_t i = 0u; i < N; ++i) {
      ret.at(i, i) = T(1);
    }
    return ret;
  }
  constexpr T& at(int i, int j) noexcept {
    return data[i * N + j];
  }
  [[nodiscard]] constexpr T at(int i, int j) const noexcept {
    return data[i * N + j];
  }
  constexpr SquareMatrix& operator*=(const SquareMatrix& other) noexcept {
    SquareMatrix mat{};
    for (std::size_t i = 0u; i < N; ++i) {
      for (std::size_t j = 0u; j < N; ++j) {
        for (std::size_t k = 0u; k < N; ++k) {
          mat.at(i, j) += at(i, k) * other.at(k, j);
        }
      }
    }
    return *this = mat;
  }
  constexpr SquareMatrix& pow(uint64_t n) noexcept {
    auto ret = SquareMatrix::id();
    for (; n > 0; n >>= 1, *this *= *this) {
      if (n % 2 == 1) {
        ret *= *this;
      }
    }
    return *this = ret;
  }
  template <typename U, std::size_t M> friend std::ostream& operator<<(std::ostream& out, const SquareMatrix<U, M>& mat) {
    for (std::size_t i = 0u; i < M; ++i) {
      for (std::size_t j = 0u; j < M; ++j) {
        out << mat.at(i, j) << ' ';
      }
      out << '\n';
    }
    return out;
  }
};