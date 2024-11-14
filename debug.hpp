#include <bits/stdc++.h>

namespace debug {

namespace detail {

template <typename Tuple, size_t... I>
void PrintTuple(std::ostream& os, Tuple tuple, std::index_sequence<I...>) {
  os << '(';
  (..., (operator<<(os, I == 0 ? "" : ", "), operator<<(os, std::get<I>(tuple))));
  os << ')';
}

} // namespace detail


template <typename ... T>
std::ostream& operator<<(std::ostream &os, std::tuple<T...> tuple) {
  detail::PrintTuple(os, std::forward<decltype(tuple)>(tuple), std::make_index_sequence<sizeof...(T)>{});
  return os;
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, std::pair<T, U> pair) {
  return os << '(' << pair.first << ", " << pair.second << ')';
}

std::ostream& operator<<(std::ostream& os, std::vector<bool> vector) {
  os << '[';
  for (auto sep = ""; auto f : vector) {
    os << std::exchange(sep, " ") << "01"[f];
  }
  return os << ']';
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> vector) {
  os << '[';
  for (auto sep = ""; auto f : vector) {
    os << std::exchange(sep, " ") << f;
  }
  return os << ']';
}

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, std::array<T, N> array) {
  os << '[';
  for (auto sep = ""; auto f : array) {
    os << std::exchange(sep, " ") << f;
  }
  return os << ']';
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::set<T> set) {
  os << '{';
  for (auto sep = ""; auto f : set) {
    os << std::exchange(sep, " ") << f;
  }
  return os << '}';
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::multiset<T> multiset) {
  os << '{';
  for (auto sep = ""; auto f : multiset) {
    os << std::exchange(sep, " ") << f;
  }
  return os << '}';
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::unordered_set<T> unorderedSet) {
  os << '{';
  for (auto sep = ""; auto f : unorderedSet) {
    os << std::exchange(sep, " ") << f;
  }
  return os << '}';
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, std::map<T, U> map) {
  os << '{';
  for (auto sep = ""; auto [k, v] : map) {
    os << std::exchange(sep, " ") << k << ": " << v;
  }
  return os << '}';
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, std::unordered_map<T, U> uMap) {
  os << '{';
  for (auto sep = ""; auto [k, v] : uMap) {
    os << std::exchange(sep, " ") << k << ": " << v;
  }
  return os << '}';
}

std::ostream& operator<<(std::ostream& os, std::integral auto&& x) {
  return os << x;
}

std::ostream& operator<<(std::ostream& os, bool f) {
  return os << (f ? "True" : "False");
}

std::ostream& operator<<(std::ostream& os, const char *str) {
  return os << std::string(str);
}

void Print() {
  std::cerr << std::endl;
}

template <typename Head, typename... Tail>
void Print(Head head, Tail ... tail) {
  std::cerr << " ";
  operator<<(std::cerr, std::forward<Head>(head));
  Print(std::forward<Tail>(tail)...);
}

} // namespace debug

#define dbg(...) std::cerr << "[" << #__VA_ARGS__ << "]:", debug::Print(__VA_ARGS__)
