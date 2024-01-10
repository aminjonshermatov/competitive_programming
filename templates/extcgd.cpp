//
// Created by aminjon on 1/11/24.
//
#include <bits/stdc++.h>

template <typename T> T extgcd(T a, T b, T& x, T& y) {
  T d = a;
  if (b != 0){
    d = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
  } else {
    x = 1;
    y = 0;
  }
  return d;
}
template <typename T> decltype(auto) extgcd(T a, T b) {
  T x, y;
  extgcd(a, b, x, y);
  return std::pair(x, y);
}
template <typename T> T inverse(T a, const T mod){
  assert(std::gcd(a, mod) == 1);
  T x, y;
  extgcd(a, mod, x, y);
  return (x % mod + mod) % mod;
}