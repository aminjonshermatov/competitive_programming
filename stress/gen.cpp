#include <print>

#include "utils.hpp"

auto gen() {
  std::println("{} {}", utils::randomInt(1, 10), utils::randomInt(1, 10));
}

int main() {
  gen();
}