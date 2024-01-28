#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

template <typename T> struct LinearFunction {
  T k, m;
  LinearFunction(T k_, T m_) : k(k_), m(m_) { }
  LinearFunction() : LinearFunction(0, std::numeric_limits<T>::max()) { }
  // evaluate value function at point `x`
  [[nodiscard]] inline T operator()(const T& x) const { return k * x + m; }
  [[nodiscard]] inline bool beats(const LinearFunction<T>& other, const T& x) const {
    return operator()(x) < other(x); // minimization
  }
  [[nodiscard]] inline bool operator==(const LinearFunction<T>& other) const {
    return k == other.k && m == other.m;
  }
  template <typename U> friend std::ostream& operator<<(std::ostream& out, const LinearFunction<U>& line) {
    return out << "y=" << line.k << 'x' << (line.m >= 0 ? '+' : '-') << std::abs(line.m);
  }
};

template <typename T> struct LiChaoNode {
  LiChaoNode *lc, *rc;
  LinearFunction<T> line;
  LiChaoNode(LiChaoNode* lc_, LiChaoNode* rc_, LinearFunction<T> line_) : lc(lc_), rc(rc_), line(line_) { }
  LiChaoNode() : LiChaoNode(nullptr, nullptr, {}) { }
  LiChaoNode(const LiChaoNode<T>& other) : LiChaoNode(other.lc, other.rc, other.line) { }
  explicit LiChaoNode(LinearFunction<T> line_) : LiChaoNode(nullptr, nullptr, line_) { }
};

template <typename T> void addLineInplace(LiChaoNode<T>*& node, T lx, T rx, LinearFunction<T> line) {
  if (node == nullptr) {
    node = new LiChaoNode<T>(line);
    return;
  }
  auto mid = lx + (rx - lx) / 2;

  auto fLeft = line.beats(node->line, lx);
  auto fMid = line.beats(node->line, mid);

  if (fMid) {
    std::swap(line, node->line);
  }
  if (rx - lx == 1) {
    return;
  }
  if (fLeft != fMid) {
    addLineInplace(node->lc, lx, mid, line);
  } else {
    addLineInplace(node->rc, mid, rx, line);
  }
}
template <typename T> LiChaoNode<T>* addLine(const LiChaoNode<T>* node, T lx, T rx, LinearFunction<T> line) {
  if (node == nullptr) {
    return new LiChaoNode<T>(line);
  }
  auto mid = lx + (rx - lx) / 2;

  auto fLeft = line.beats(node->line, lx);
  auto fMid = line.beats(node->line, mid);

  auto newNode = node;
  if (fMid) {
    newNode = new LiChaoNode(*node);
    std::swap(line, newNode->line);
  }
  if (rx - lx == 1) {
    return newNode;
  }
  if (fLeft != fMid) {
    if (newNode == node) {
      newNode = new LiChaoNode(*node);
    }
    newNode->lc = addLine(newNode->lc, lx, mid, line);
  } else {
    if (newNode == node) {
      newNode = new LiChaoNode(*node);
    }
    newNode->rc = addLine(newNode->rc, mid, rx, line);
  }
  return newNode;
}
template <typename T> void merge(LiChaoNode<T>* dest, LiChaoNode<T>* from, T lx, T rx) {
  if (from == nullptr) {
    return;
  }
  addLineInplace(dest, lx, rx, from->line);
  if (from->lc != nullptr) {
    merge(dest, from->lc, lx, rx);
  }
  if (from->rc != nullptr) {
    merge(dest, from->rc, lx, rx);
  }
}
template <typename T> T query(const LiChaoNode<T>* node, T lx, T rx, const T& x) noexcept {
  if (node == nullptr) {
    return std::numeric_limits<T>::max();
  }
  auto loc = node->line(x);
  if (rx - lx > 1) {
    auto mid = lx + (rx - lx) / 2;
    loc = std::min(loc, x < mid ? query(node->lc, lx, mid, x) : query(node->rc, mid, rx, x));
  }
  return loc;
}

using i64 = int64_t;
using Line = LinearFunction<i64>;
using Node = LiChaoNode<i64>;

void solve() {
  int n;
  i64 C;
  std::cin >> n >> C;
  std::vector<i64> H(n);
  for (auto& h : H) {
    std::cin >> h;
  }

  if (false) {
    constexpr auto inf = std::numeric_limits<i64>::max();
    std::vector<i64> dp(n, inf);
    dp[0] = 0;
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        dbg(i,j,dp[j] + (H[i] - H[j]) * (H[i] - H[j]) + C);
        dp[i] = std::min(dp[i], dp[j] + (H[i] - H[j]) * (H[i] - H[j]) + C);
      }
    }
  }
  // dp[i] min= dp[j] + (H[i] - H[j])^2 + C, j < i
  // dp[i] min= dp[j] + H[i]^2 - 2*H[i]*H[j] + H[j]^2 + C, j < i
  // dp[i] min= -2*H[i]*H[j] + H[j]^2 + dp[j] + C + H[i]^2, j < i

  const auto max_h = std::ranges::max(H);
  auto root = new Node();
  addLineInplace(root, i64(0), max_h + 1, Line{-2 * H[0], H[0] * H[0] + 0});
  for (int i = 1; i < n; ++i) {
    auto val = query(root, i64(0), max_h + 1, H[i]) + C + H[i] * H[i];
    if (i + 1 == n) {
      std::cout << val << '\n';
      return;
    }
    addLineInplace(root, i64(0), max_h + 1, Line{-2 * H[i], val + H[i] * H[i]});
  }
  assert(false);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
