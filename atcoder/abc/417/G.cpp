#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

constexpr int64_t kMaxLen = 1E18 + 1;

struct Node {
  Node *Lc = nullptr, *Rc = nullptr;
  char C = '#';
  int64_t Len = 0;
  Node() = default;
  explicit Node(char c) : C(c), Len(1) { }
  Node(Node *a, Node *b) : Lc(a), Rc(b) {
    if (a != nullptr) {
      Len = std::min<__int128>(__int128(Len) + a->Len, kMaxLen);
    }
    if (b != nullptr) {
      Len = std::min<__int128>(__int128(Len) + b->Len, kMaxLen);
    }
  }
};

char GetKth(Node *node, int64_t kth) {
  assert(node->Len >= kth);
  if (node->C != '#') {
    assert(kth == 1);
    return node->C;
  }
  assert(node->Lc != nullptr);
  if (node->Lc->Len >= kth) {
    return GetKth(node->Lc, kth);
  }
  assert(node->Rc != nullptr);
  return GetKth(node->Rc, kth - node->Lc->Len);
}

void Solve() {
  int q;
  Scan(q);

  std::vector<Node*> nodes;
  nodes.reserve(q + 2);
  nodes.emplace_back(new Node('0'));
  nodes.emplace_back(new Node('1'));
  while (q-- > 0) {
    int l, r;
    int64_t x;
    Scan(l, r, x);

    nodes.emplace_back(new Node(nodes[l], nodes[r]));
    Println(GetKth(nodes.back(), x));
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);


  Solve();
}
