#include <bits/stdc++.h>
#include "constants.h"

void solve(std::istream &in, std::ostream &out) {
  int n;
  in >> n;
  std::vector<std::string> ss(n);
  std::vector<int> q_pos(n);
  for (int i = 0; i < n; ++i) {
    in >> ss[i];
    q_pos[i] = ss[i].find('?');
  }

  for (int m = 0; m < (1 << n); ++m) {
    std::vector<std::pair<std::string, int>> cur(n);
    for (int i = 0; i < n; ++i) {
      cur[i].first = ss[i];
      cur[i].second = i;
      if (q_pos[i] == std::string::npos) continue;
      cur[i].first[q_pos[i]] = char('0' + (m >> i & 1));
    }
    std::sort(cur.begin(), cur.end(), [](const auto &lhs, const auto &rhs) {
      return lhs.first < rhs.first;
    });
    bool ok = true;
    for (int i = 1; i < n && ok; ++i) {
      ok &= !cur[i].first.starts_with(cur[i - 1].first);
    }
    if (ok) {
      out << "YES\n";
      std::sort(cur.begin(), cur.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.second < rhs.second;
      });
      for (auto &[s, _] : cur) {
        out << s << '\n';
      }
      return;
    }
  }
  out << "NO\n";
}

int main() {
  std::ifstream in(constants::DATA_IN);
  std::ofstream out(constants::SLOW_OUT);

  solve(in, out);

  return 0;
}
