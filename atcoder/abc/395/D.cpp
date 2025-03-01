#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void Solve() {
  int n, q;
  Scan(n, q);

  std::vector<std::set<int>> nests(n);
  std::vector<int> pigeon2nest(n), nest2label(n), label2nest(n);
  for (auto i = 0; i < n; ++i) {
    nests[i].emplace(i);
    pigeon2nest[i] = i;
    nest2label[i] = i;
    label2nest[i] = i;
  }

  while (q-- > 0) {
    char cmd;
    Scan(cmd);
    if (cmd == '1') {
      int pigeon, newLabel;
      Scan(pigeon, newLabel);
      --pigeon, --newLabel;

      auto currentNestPos = pigeon2nest[pigeon];
      if (auto it = nests[currentNestPos].find(pigeon); it != nests[currentNestPos].end()) {
        nests[currentNestPos].erase(it);
      } else {
        assert(false);
      }
      const auto nestPos = label2nest[newLabel];
      pigeon2nest[pigeon] = nestPos;
      nests[nestPos].emplace(pigeon);
    } else if (cmd == '2') {
      int labelA, labelB;
      Scan(labelA, labelB);
      --labelA, --labelB;

      const auto nestA = label2nest[labelA], nestB = label2nest[labelB];
      nest2label[nestA] = labelB;
      label2nest[labelB] = nestA;

      nest2label[nestB] = labelA;
      label2nest[labelA] = nestB;
    } else if (cmd == '3') {
      int pigeon;
      Scan(pigeon);
      --pigeon;

      Println(nest2label[pigeon2nest[pigeon]] + 1);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
