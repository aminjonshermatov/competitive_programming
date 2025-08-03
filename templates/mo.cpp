//
// Created by aminjon on 3/11/23.
//
#include <bits/stdc++.h>

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

    int curL = 0, curR = -1;
    for (const auto id : ord) {
      const auto [l, r] = Queries_[id];
      while (curL > l) {
        addLeft(--curL);
      }
      while (curR < r) {
        addRight(++curR);
      }
      while (curL < l) {
        removeLeft(curL++);
      }
      while (curR > r) {
        removeRight(curR--);
      }
      pull(id);
    }
  }

 private:
  std::vector<std::pair<int, int>> Queries_;
};

/*
auto addLeft = [&](const int pos) {};
auto addRight = [&](const int pos) {};
auto removeLeft = [&](const int pos) {};
auto removeRight = [&](const int pos) {};
auto pull = [&](const int qId) {};
mo.Run(
  addLeft, addRight, removeLeft, removeRight,
  pull, [] {
    return 1000;
  }()
);
*/

// 3D Mo's algo
// https://gist.github.com/aminjonshermatov/8c34af802c075264b24615a971a0c09c