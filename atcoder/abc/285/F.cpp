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

constexpr int kSigma = 26;

class Info {
 public:
  std::array<int, kSigma> Qty{};
};
Info operator+(const Info& lhs, const Info& rhs) {
  Info ret{};
  for (int i = 0; i < kSigma; ++i) {
    ret.Qty[i] = lhs.Qty[i] + rhs.Qty[i];
  }
  return ret;
}

void Solve() {
  int n, q;
  std::string s;
  Scan(n, s, q);

  BottomUpSegmentTree<Info> st(n);
  std::array<int, kSigma> tot{};
  for (int i = 0; i < n; ++i) {
    ++tot[s[i] - 'a'];
    st.Modify(i, {[c = s[i]] {
      std::array<int, kSigma> qty{};
      ++qty[c - 'a'];
      return qty;
    }()});
  }

  while (q-- > 0) {
    char cmd;
    Scan(cmd);
    if (cmd == '1') {
      int x;
      char c;
      Scan(x, c);
      --x;

      auto [qty] = st.Query(x);
      --qty[s[x] - 'a'];
      --tot[s[x] - 'a'];
      s[x] = c;
      ++tot[s[x] - 'a'];
      ++qty[s[x] - 'a'];
      st.Modify(x, {qty});
    } else {
      int l, r;
      Scan(l, r);
      --l, --r;

      const auto [qty] = st.Query(l, r + 1);
      auto ok = true;
      auto fst = -1, lst = -1;
      for (int c = 0, offset = 0; c < kSigma; ++c) {
        const auto [loc] = st.Query(l + offset, l + offset + qty[c]);
        for (int x = 0; x < kSigma; ++x) {
          ok &= x == c ? loc[x] == qty[c] : loc[x] == 0;
        }
        if (qty[c] > 0) {
          offset += qty[c];
          if (fst == -1) {
            fst = c;
          }
          lst = c;
        }
      }
      for (int c = fst + 1; c < lst; ++c) {
        ok &= tot[c] == qty[c];
      }

      Println(ok ? "Yes" : "No");
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
