#include <iostream>

#include "config.hpp"

auto slow() {
  int a, b;
  std::cin >> a >> b;
  std::cout << a + b << '\n';
}

int main() {
  slow();
}