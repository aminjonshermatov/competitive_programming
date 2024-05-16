#include <iostream>

#include "utils.hpp"

auto gen() {
  std::cout << utils::randomInt(1, 10) << ' ' << utils::randomInt(1, 10) << '\n';
}

int main() {
  gen();
}