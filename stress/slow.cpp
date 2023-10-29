#include <bits/stdc++.h>
#include "constants.h"

void solve(std::istream &in, std::ostream &out) {
  int n;
  in >> n;
  std::vector<int> ps(n);
  for (auto &v : ps) {
    in >> v;
  }

  int q;
  in >> q;
  while (q--) {
    int l, r;
    in >> l >> r;
    std::vector<int> cnt(n, 0);
    std::vector<bool> used(n, false);
    auto dfs = [&](auto &f, int v) -> void {
      used[v] = true;
      ++cnt[v];
      if (!used[ps[v]]) {
        f(f, ps[v]);
      }
    };
    for (int i = l; i <= r; ++i) {
      if (!used[i]) {
        dfs(dfs, i);
      }
    }
    int mex = -1;
    for (int i = 0; i < n && mex == -1; ++i) {
      if (cnt[i] == 0) {
        mex = i;
      }
    }
    if (mex == -1) {
      mex = n;
    }
    out << mex << '\n';
  }
}

bool is_multi = false;

int main() {
  std::ifstream in(constants::DATA_IN);
  std::ofstream out(constants::SLOW_OUT);

  solve(in, out);

  return 0;
}
