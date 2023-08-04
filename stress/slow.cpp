#include <bits/stdc++.h>
#include "constants.h"

using namespace std;

using i64 = int64_t;

void solve(istream &cin, ostream &cout) {
  int n; cin >> n;
  vector<string> ws(n);
  for (auto &w : ws) cin >> w;

  int q; cin >> q;
  while (q--) {
    string p;
    int k;
    cin >> p >> k;

    vector<pair<string, int>> nw;
    for (int i = 0; i < n; ++i) {
      if (ws[i].starts_with(p)) {
        nw.emplace_back(ws[i], i);
      }
    }
    sort(nw.begin(), nw.end());
    if (nw.size() < k) {
      cout << -1 << '\n';
      continue;
    }
    cout << nw[k - 1].second + 1 << '\n';
  }
}

bool is_multi = false;

int main() {
  ifstream in(constants::DATA_IN);
  ofstream out(constants::SLOW_OUT);

  solve(in, out);

  return 0;
}
