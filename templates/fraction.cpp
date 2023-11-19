//
// Created by Aminjon Shermatov !Yandex on 20.11.2023.
//
#include <bits/stdc++.h>

template <typename T> class Fraction {
  T numerator, denominator;
  void reduce() {
    auto g = std::gcd(numerator, denominator);
    numerator /= g;
    denominator /= g;
  }
public:
  explicit Fraction(T numerator_ = T(0), T denominator_ = T(1)) : numerator(numerator_), denominator(denominator_) { assert(denominator != T(0)); reduce(); }

  Fraction operator-() const {
    return Fraction(-numerator, denominator);
  }

  Fraction operator+(const Fraction<T> &other) const {
    return Fraction(numerator * other.denominator + denominator * other.numerator, denominator * other.denominator);
  }
  Fraction operator-(const Fraction<T> &other) const {
    return Fraction(numerator * other.denominator - denominator * other.numerator, denominator * other.denominator);
  }
  Fraction operator*(const Fraction<T> &other) const {
    return Fraction(numerator * other.numerator, denominator * other.denominator);
  }
  Fraction operator/(const Fraction<T> &other) const {
    return Fraction(numerator * other.denominator, denominator * other.numerator);
  }

  bool operator<(const Fraction<T> &other) const {
    return numerator * other.denominator < denominator * other.numerator;
  }
  bool operator>(const Fraction<T> &other) const {
    return numerator * other.denominator > denominator * other.numerator;
  }
  bool operator==(const Fraction<T> &other) const {
    return numerator == other.numerator && denominator == other.denominator;
  }

  [[nodiscard]] long double toLongDouble() const {
    return (long double)(numerator) / denominator;
  }

  [[maybe_unused]] static constexpr char DELIMETER = '/';
  template <typename U> friend std::istream& operator>>(std::istream &in, Fraction<U> &fraction) {
    in >> fraction.numerator;
    char _;
    in >> _;
    assert(_ == DELIMETER);
    in >> fraction.denominator;
    assert(fraction.denominator != U(0));
    return in;
  }
  template <typename U> friend std::ostream& operator<<(std::ostream &out, const Fraction<U> &fraction) {
    return out << fraction.numerator << DELIMETER << fraction.denominator;
  }
};
using Frac = Fraction<int>;
