#include <iostream>

#include "config.hpp"

auto fast() {
  int a, b;
  std::cin >> a >> b;
  std::cout << a + b << '\n';
}

int main() {
  fast();
}