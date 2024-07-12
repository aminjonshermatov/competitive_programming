#include <iostream>

#include "utils.hpp"

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

auto gen() {
  println(utils::randomInt(1, 10), utils::randomInt(1, 10));
}

int main() {
  gen();
}