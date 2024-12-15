#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

template <typename T>
class FenwickTreePointUpdateRangeQuery {
 public:
  FenwickTreePointUpdateRangeQuery() = default;
  explicit FenwickTreePointUpdateRangeQuery(const int n)
    : N_(n), Bit_(n, T{})
  { }
  template<typename U>
  explicit FenwickTreePointUpdateRangeQuery(const std::vector<U> &as)
    : N_(static_cast<int>(as.size())), Bit_(as.size(), T{})
  {
    for (auto idx = 0; idx < N_; ++idx) {
      Modify(idx, T{as[idx]});
    }
  }

  auto Reset(const int n) {
    N_ = n;
    Bit_.assign(n, T{});
  }

  auto Modify(const int idx, const T& val) {
    for (auto id = idx; id < N_; id = id | (id + 1)) {
      Bit_[id] = Bit_[id] + val;
    }
  }

  auto Query(const int idx) const -> T {
    auto ret = T{};
    for (auto id = idx; id >= 0; id = (id & (id + 1)) - 1) {
      ret = ret + Bit_[id];
    }
    return ret;
  }

  // [l, r)
  auto Query(const int l, const int r) const -> T {
    return Query(r - 1) - Query(l - 1);
  }

 private:
  int N_{0};
  std::vector<T> Bit_;
};

class Info {
 public:
  Info() = default;
  explicit Info(const int64_t val)
   : Sum(val), Cnt(1)
  { }
  Info(const int64_t sum, const int64_t cnt)
    : Sum(sum), Cnt(cnt)
  { }

  Info operator+(const Info& other) {
    return {
      Sum + other.Sum,
      Cnt + other.Cnt
    };
  }
  Info operator-(const Info& other) {
    return {
      Sum - other.Sum,
      Cnt - other.Cnt
    };
  }

 public:
  int64_t Sum{0}, Cnt{0};
};

class Mo {
 public:
  void Add(const int l, const int r) {
    Queries_.emplace_back(l, r);
  }

  void Run(
    auto&& addLeft, auto&& addRight, auto&& removeLeft, auto&& removeRight,
    auto&& pull, const int blockWidth
  ) {
    std::vector<std::size_t> ord(Queries_.size());
    std::iota(ord.begin(), ord.end(), std::size_t{0});
    std::ranges::sort(
      ord,
      [blockWidth, &queries = std::as_const(Queries_)](const std::size_t a, const std::size_t b) {
        auto [lA, rA] = queries[a];
        auto [lB, rB] = queries[b];
        lA /= blockWidth;
        lB /= blockWidth;
        return lA != lB ? lA < lB : lA % 2 == 1 ? rA > rB : rA < rB;
      }
    );

    int curL = -1, curR = -1;
    for (const auto id : ord) {
      const auto [l, r] = Queries_[id];
      while (curL > l) {
        addLeft(--curL + 1);
      }
      while (curR < r) {
        addRight(curR++ + 1);
      }
      while (curL < l) {
        removeLeft(curL++ + 1);
      }
      while (curR > r) {
        removeRight(--curR + 1);
      }
      pull(id);
    }
  }

 private:
  std::vector<std::pair<int, int>> Queries_;
};

void Solve() {
  int n;
  Scan(n);
  std::vector<int> as(n), bs(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }
  for (int i = 0; i < n; ++i) {
    Scan(bs[i]);
  }

  auto all = as;
  all.insert(all.end(), bs.begin(), bs.end());
  std::ranges::sort(all);
  all.erase(std::ranges::unique(all).begin(), all.end());
  const auto m = static_cast<int>(all.size());
  for (int i = 0; i < n; ++i) {
    as[i] = std::distance(all.begin(), std::ranges::lower_bound(all, as[i]));
    bs[i] = std::distance(all.begin(), std::ranges::lower_bound(all, bs[i]));
  }

  int q;
  Scan(q);
  Mo mo;
  for (int i = 0; i < q; ++i) {
    int l, r;
    Scan(l, r);
    mo.Add(l - 1, r - 1);
  }

  int64_t cur = 0;
  int64_t sumA = 0, sumB = 0;
  FenwickTreePointUpdateRangeQuery<Info> ftA(m), ftB(m);

  auto addLeft = [&](int pos) {
    // remove pos from a
    const auto [bSumLt, bCntLt] = ftB.Query(0, as[pos]);
    const auto [bSumGe, bCntGe] = ftB.Query(as[pos], m);
    cur -= bCntLt * all[as[pos]] - bSumLt + bSumGe - bCntGe * all[as[pos]];
    sumA -= all[as[pos]];
    ftA.Modify(as[pos], {-all[as[pos]], -1});
  };
  auto addRight = [&](int pos) {
    // add pos from b
    const auto [aSumLt, aCntLt] = ftA.Query(0, bs[pos]);
    const auto [aSumGe, aCntGe] = ftA.Query(bs[pos], m);
    cur += aCntLt * all[bs[pos]] - aSumLt + aSumGe - aCntGe * all[bs[pos]];
    sumB += all[bs[pos]];
    ftB.Modify(bs[pos], {+all[bs[pos]], +1});
  };
  auto removeLeft = [&](int pos) {
    // add pos from a
    const auto [bSumLt, bCntLt] = ftB.Query(0, as[pos]);
    const auto [bSumGe, bCntGe] = ftB.Query(as[pos], m);
    cur += bCntLt * all[as[pos]] - bSumLt + bSumGe - bCntGe * all[as[pos]];
    sumA += all[as[pos]];
    ftA.Modify(as[pos], {+all[as[pos]], +1});
  };
  auto removeRight = [&](int pos) {
    // remove pos from b
    const auto [aSumLt, aCntLt] = ftA.Query(0, bs[pos]);
    const auto [aSumGe, aCntGe] = ftA.Query(bs[pos], m);
    cur -= aCntLt * all[bs[pos]] - aSumLt + aSumGe - aCntGe * all[bs[pos]];
    sumB -= all[bs[pos]];
    ftB.Modify(bs[pos], {-all[bs[pos]], -1});
  };
  std::vector<int64_t> ret(q);
  auto pull = [&](int id) {
    ret[id] = cur;
  };
  mo.Run(
    addLeft, addRight, removeLeft, removeRight,
    pull, [] {
      return 1000;
    }()
  );

  for (int i = 0; i < q; ++i) {
    Println(ret[i]);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
