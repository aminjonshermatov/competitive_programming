#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

template <typename T> struct LinearFunction {
  T k, m;
  LinearFunction(T k_, T m_) : k(k_), m(m_) { }
  LinearFunction() : LinearFunction(0, 1e13) { }
  // evaluate value function at point `x`
  [[nodiscard]] inline T operator()(const T& x) const { return k * x + m; }
  [[nodiscard]] inline bool beats(const LinearFunction<T>& other, const T& x) const {
    return operator()(x) < other(x); // minimization
  }

  template <typename U> friend std::ostream& operator<<(std::ostream& out, const LinearFunction<U>& line) {
    return out << "y=" << line.k << 'x' << (line.m >= 0 ? '+' : '-') << std::abs(line.m);
  }
};

template <typename T> struct LiChaoNode {
  T lBound{}, rBound{};
  LiChaoNode *lChild, *rChild;
  LinearFunction<T> optLine;

  LiChaoNode(T lb, T rb, LiChaoNode *lCh, LiChaoNode *rCh) : lBound(lb), rBound(rb), lChild(lCh), rChild(rCh) { }
  LiChaoNode(T lb, T rb) : LiChaoNode(lb, rb, nullptr, nullptr) { }

  void extend() {
    if (lChild == nullptr && rBound - lBound > 1) {
      auto mid = lBound + (rBound - lBound) / 2;
      lChild = new LiChaoNode<T>(lBound, mid);
      rChild = new LiChaoNode<T>(mid, rBound);
    }
  }

  void addLine(LinearFunction<T> line) {
    auto mid = lBound + (rBound - lBound) / 2;

    auto fLeft = line.beats(optLine, lBound);
    auto fMid = line.beats(optLine, mid);

    if (fMid) {
      std::swap(line, optLine);
    }
    if (rBound - lBound == 1) {
      return;
    }
    extend();
    (fLeft != fMid ? lChild : rChild)->addLine(line);
  }
  [[nodiscard]] auto query(const T& x) {
    auto loc = optLine(x);
    if (rBound - lBound == 1) {
      return loc;
    }
    auto mid = lBound + (rBound - lBound) / 2;
    extend();
    return std::min(loc, (x < mid ? lChild : rChild)->query(x));
  }
};

using i64 = int64_t;

void solve() {
  int n;
  i64 x;
  std::cin >> n >> x;
  std::vector<i64> ss(n), fs(n);
  i64 max_x = 0;
  for (auto& s : ss) {
    std::cin >> s;
    max_x = std::max(max_x, s);
  }
  for (auto& f : fs) {
    std::cin >> f;
    max_x = std::max(max_x, f);
  }

  LiChaoNode<i64> root(0, max_x + 1);
  root.addLine({x, 0});
  i64 ans;
  for (int i = 0; i < n; ++i) {
    auto dpj = root.query(ss[i]);
    if (i + 1 == n) {
      ans = dpj;
    }
    root.addLine({fs[i], dpj});
  }
  std::cout << ans << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}