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
class FenwickTree {
 public:
  FenwickTree() = default;
  explicit FenwickTree(const int n) {
    Init(std::vector(n, Info{}));
  }
  FenwickTree(const int n, const Info& info) {
    Init(std::vector(n, info));
  }
  template<typename U>
  explicit FenwickTree(const std::vector<U>& as) {
    std::vector<Info> init(as.size());
    std::ranges::generate(init, [id = std::size_t{0}, &as]() mutable {
      return Info{as[id++]};
    });
    Init(init);
  }

  auto Init(const std::vector<Info>& init) {
    N_ = static_cast<int>(init.size());
    Bit_.assign(N_, Info{});
    for (int i = 0; i < N_; ++i) {
      Modify(i, init[i]);
    }
  }

  auto Modify(const int idx, const Info& val) {
    for (auto id = idx; id < N_; id = id | (id + 1)) {
      Bit_[id] = Bit_[id] + val;
    }
  }

  auto Query(const int idx) const -> Info {
    return Query(idx, idx + 1);
  }

  // [l, r)
  auto Query(const int l, const int r) const -> Info {
    return QueryImpl(r - 1) - QueryImpl(l - 1);
  }

 private:
  auto QueryImpl(const int idx) const -> Info {
    auto ret = Info{};
    for (auto id = idx; id >= 0; id = (id & (id + 1)) - 1) {
      ret = ret + Bit_[id];
    }
    return ret;
  }

 private:
  int N_{0};
  std::vector<Info> Bit_;
};

void Solve() {
  int n, q;
  Scan(n, q);

  std::vector whenR(n, 0), whenC(n, 0);
  FenwickTree<int> cntR(q + 5), cntC(q + 5);
  cntR.Modify(0, n);
  cntC.Modify(0, n);
  auto b = 0LL;
  for (int t = 1; t <= q; ++t) {
    char cmd;
    Scan(cmd);
    if (cmd == '1') {
      int r;
      Scan(r);
      --r;

      b += n - cntC.Query(0, whenR[r]);
      cntR.Modify(whenR[r], -1);
      whenR[r] = t;
      cntR.Modify(whenR[r], +1);
    } else {
      int c;
      Scan(c);
      --c;

      b -= cntR.Query(whenC[c] + 1, q + 1);
      cntC.Modify(whenC[c], -1);
      whenC[c] = t;
      cntC.Modify(whenC[c], +1);
    }
    Print(b);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
