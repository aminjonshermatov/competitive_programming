#include <bits/stdc++.h>

namespace debug {

  template<class Tuple, size_t... I> void print_tuple_helper(std::ostream &out, const Tuple& tuple, std::index_sequence<I...>) {
    out << '(';
    (..., (operator<<(out, I == 0 ? "" : ", "), operator<<(out, std::get<I>(tuple))));
    out << ')';
  }
  template<class... T> std::ostream& operator<<(std::ostream &out, const std::tuple<T...>& tuple) {
    print_tuple_helper(out, tuple, std::make_index_sequence<sizeof...(T)>());
    return out;
  }

  template <typename T, typename U> std::ostream& operator<<(std::ostream &out, const std::pair<T, U> &pair) {
    return out << '(' << pair.first << ", " << pair.second << ')';
  }

  std::ostream& operator<<(std::ostream &out, const std::vector<bool> &vector) {
    out << '[';
    bool is_first = true;
    for (auto flag : vector) {
      if (!is_first) {
        out << ", ";
      }
      out << (flag ? '1' : '0');
      is_first = false;
    }
    return out << ']';
  }
  template<typename T> std::ostream& operator<<(std::ostream &out, const std::vector<T> &vector) {
    out << '[';
    bool is_first = true;
    for (auto element : vector) {
      if (!is_first) {
        out << ", ";
      }
      out << element;
      is_first = false;
    }
    return out << ']';
  }
  template<typename T, std::size_t N> std::ostream& operator<<(std::ostream &out, const std::array<T, N> &array) {
    out << '[';
    bool is_first = true;
    for (auto element : array) {
      if (!is_first) {
        out << ", ";
      }
      out << element;
      is_first = false;
    }
    return out << ']';
  }

  template <typename T> std::ostream& operator<<(std::ostream &out, const std::set<T> &set) {
    out << '{';
    bool is_first = true;
    for (auto x : set) {
      if (!is_first) {
        out << ", ";
      }
      out << x;
      is_first = false;
    }
    return out << '}';
  }
  template <typename T> std::ostream& operator<<(std::ostream &out, const std::multiset<T> &multiset) {
    out << '{';
    bool is_first = true;
    for (auto x : multiset) {
      if (!is_first) {
        out << ", ";
      }
      out << x;
      is_first = false;
    }
    return out << '}';
  }
  template <typename T> std::ostream& operator<<(std::ostream &out, const std::unordered_set<T> &unordered_set) {
    out << '{';
    bool is_first = true;
    for (auto x : unordered_set) {
      if (!is_first) {
        out << ", ";
      }
      out << x;
      is_first = false;
    }
    return out << '}';
  }

  template <typename T, typename U> std::ostream& operator<<(std::ostream &out, const std::map<T, U> &map) {
    out << '{';
    bool is_first = true;
    for (auto &kv : map) {
      if (!is_first) {
        out << ", ";
      }
      out << kv;
      is_first = false;
    }
    return out << '}';
  }
  template <typename T, typename U> std::ostream& operator<<(std::ostream &out, const std::unordered_map<T, U> &unordered_map) {
    out << '{';
    bool is_first = true;
    for (auto &kv : unordered_map) {
      if (!is_first) {
        out << ", ";
      }
      out << kv;
      is_first = false;
    }
    return out << '}';
  }
  template <typename T, typename U> std::ostream& operator<<(std::ostream &out, const std::multimap<T, U> &multimap) {
    out << '{';
    bool is_first = true;
    for (auto &kv : multimap) {
      if (!is_first) {
        out << ", ";
      }
      out << kv;
      is_first = false;
    }
    return out << '}';
  }

  std::ostream& operator<<(std::ostream &out, bool flag) { return out << (flag ? "True" : "False"); }
  std::ostream& operator<<(std::ostream &out, const char *s) { return out << (std::string)s; }
  template<typename T> concept Printable = requires(T t) { { std::cout << t } -> std::same_as<std::ostream&>; };
  template <Printable T> std::ostream& operator<<(std::ostream &out, const T &unknown) { return out << unknown; }

  void print() { std::cerr << std::endl; }
  template <typename Head, typename... Tail> void print(Head H, Tail... T) {
    std::cerr << " ";
    operator<<(std::cerr, H);
    print(T...);
  }
}

#define dbg(...) std::cerr << "[" << #__VA_ARGS__ << "]:", debug::print(__VA_ARGS__)
