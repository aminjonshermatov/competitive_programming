#include <bits/stdc++.h>
#include "constants.h"

using namespace std;

void solve(istream &in, ostream &out) {
  int n, q;
  in >> n >> q;

  vector<int64_t> as(n);
  for (auto &a : as) {
    in >> a;
  }
  while (q-- > 0) {
    int l1, r1, l2, r2;
    in >> l1 >> r1 >> l2 >> r2;
    --l1, --l2;
    vector<int64_t> na;
    for (int i = l1; i < r1; ++i) {
      na.emplace_back(as[i]);
    }
    for (int i = l2; i < r2; ++i) {
      na.emplace_back(as[i]);
    }
    sort(na.begin(), na.end());
    auto k = r1 - l1 + r2 - l2;
    int64_t s1 = 0, c1 = 0;
    for (int i = l1; i < r1; ++i) {
      if (as[i] >= na[k / 2]) {
        ++c1;
        s1 += as[i];
      }
    }
    int64_t s2 = 0, c2 = 0;
    for (int i = l2; i < r2; ++i) {
      if (as[i] <= na[k / 2]) {
        ++c2;
        s2 += as[i];
      }
    }
    out << s1 - c1 * na[k / 2] + c2 * na[k / 2] - s2 << '\n';
  }
}

bool is_multi = false;

int main() {
  ifstream in(constants::DATA_IN);
  ofstream out(constants::SLOW_OUT);

  solve(in, out);

  return 0;
}
