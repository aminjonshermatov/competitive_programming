#include <bits/stdc++.h>
#include "constants.h"

using namespace std;

void solve(istream &in, ostream &out) {
  using i64 = int64_t;

  int n, m;
  in >> n >> m;
  string s(n, '#');
  for (auto &c : s) {
    int x;
    in >> x;
    assert(x > 0);
    c = char('a' + x);
  }

  map<string, i64> cnt{};
  i64 ans = 0;
  string refren;
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      auto ns = s.substr(i, j - i + 1);
      ++cnt[ns];
      if (ans < cnt[ns] * ns.size()) {
        ans = cnt[ns] * ns.size();
        refren = ns;
      }
    }
  }
  out << ans << '\n';
  out << refren.size() << '\n';
  for (auto c : refren) {
    out << c - 'a' << ' ';
  }
  out << '\n';
}

bool is_multi = false;

int main() {
  ifstream in(constants::DATA_IN);
  ofstream out(constants::SLOW_OUT);

  solve(in, out);

  return 0;
}
