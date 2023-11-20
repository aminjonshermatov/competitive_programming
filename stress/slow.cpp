#include <bits/stdc++.h>
#include "constants.h"

void solve(std::istream &in, std::ostream &out) {
  int n, q;
  in >> n >> q;

  using i64 = int64_t;

  std::vector<std::tuple<char, i64, i64>> evs(n);
  for (auto &[op, t, k] : evs) {
    in >> op >> t >> k;
  }

  for (int i = 0; i < q; ++i) {
    i64 cur;
    in >> cur;

    // <time, cnt>
    std::queue<std::pair<i64, i64>> Q;
    i64 tot = 0;
    for (auto [op, t, k] : evs) {
      if (op == '+') {
        cur += k;
      } else {
        Q.emplace(t, k);
      }
      while (!Q.empty() && cur > 0) {
        auto &[tt, cnt] = Q.front();
        auto min = std::min(cur, cnt);
        tot += min * (t - tt);
        cur -= min;
        cnt -= min;
        if (cnt == 0) {
          Q.pop();
        }
      }
    }
    if (!Q.empty()) {
      out << "INFINITY\n";
      continue;
    }
    out << tot << '\n';
  }
}

int main() {
  std::ifstream in(constants::DATA_IN);
  std::ofstream out(constants::SLOW_OUT);

  solve(in, out);

  return 0;
}
