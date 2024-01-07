//
// Created by Aminjon Shermatov on 10.12.2023.
//

#include <bits/stdc++.h>

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
