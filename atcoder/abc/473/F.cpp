#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

template <typename Info>
class BottomUpSegmentTree {
public:
  BottomUpSegmentTree() = default;

  explicit BottomUpSegmentTree(std::size_t n) {
    Init(std::vector(n, Info{}));
  }
  BottomUpSegmentTree(std::size_t n, Info&& info) {
    Init(std::vector(n, std::forward<Info>(info)));
  }
  template <typename T>
  explicit BottomUpSegmentTree(const std::vector<T>& init) {
    Init(init);
  }

  template <typename T>
  void Init(const std::vector<T>& init) {
    assert(!init.empty());
    N_ = 1u << (std::bit_width(2 * init.size() - 1) - 1);
    Infos_.assign(2 * N_, Info{});
    for (std::size_t i{0}; i < init.size(); ++i) {
      Infos_[i + N_] = Info{init[i]};
    }
    for (std::size_t i = N_ - 1; i >= 1u; --i) {
      Infos_[i] = Infos_[i << 1] + Infos_[i << 1 | 1];
    }
  }

  void Modify(std::size_t pos, Info&& val) {
    Infos_[pos += N_] = val;
    for (pos >>= 1; pos >= 1; pos >>= 1) {
      Infos_[pos] = Infos_[pos << 1] + Infos_[pos << 1 | 1];
    }
  }

  Info Query(std::size_t l, std::size_t r) {
    auto retL = Info{}, retR = Info{};
    for (l += N_, r += N_; l < r; l >>= 1, r >>= 1) {
      if (l % 2 == 1u) {
        retL = retL + Infos_[l++];
      }
      if (r % 2 == 1u) {
        retR = Infos_[--r] + retR;
      }
    }
    return retL + retR;
  }

  Info Query(std::size_t pos) {
    return Query(pos, pos + 1);
  }

private:
  std::size_t N_{0};
  std::vector<Info> Infos_;
};

class Info {
public:
  int Len = 0;
  int Sum = 0;
  int Min = std::numeric_limits<int>::max() / 3;
};
Info operator+(const Info& lhs, const Info& rhs) {
  if (lhs.Len == 0) {
    return rhs;
  }
  if (rhs.Len == 0) {
    return lhs;
  }
  Info info;
  info.Len = lhs.Len + rhs.Len;
  info.Sum = lhs.Sum + rhs.Sum;
  info.Min = std::min(lhs.Min, rhs.Min + lhs.Sum);
  return info;
}

void Solve() {
  int n, q;
  std::string s;
  Scan(n, s, q);

  BottomUpSegmentTree<Info> st(n);
  for (int i = 0; i < n; ++i) {
    const auto x = s[i] == 'A' ? +1 : -1;
    st.Modify(i, Info{1, x, x});
  }

  while (q-- > 0) {
    char cmd;
    Scan(cmd);
    if (cmd == '1') {
      int i;
      char c;
      Scan(i, c);
      --i;

      if (s[i] == c) {
        continue;
      }
      if (s[i] == 'A') {
        assert(c == 'B');
        st.Modify(i, Info{1, -1, -1});
      } else {
        assert(c == 'A');
        st.Modify(i, Info{1, +1, +1});
      }
      s[i] = c;
    } else if (cmd == '2') {
      int l, r;
      Scan(l, r);
      --l, --r;

      Println(st.Query(l, r + 1).Min >= 0 ? "Yes" : "No");
    } else {
      assert(false);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
