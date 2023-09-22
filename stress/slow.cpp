#include <bits/stdc++.h>
#include "constants.h"

using namespace std;

void solve(istream &in, ostream &out) {
  string a, b;
  int k;
  in >> a >> b >> k;
  set<string> aa, bb;
  for (int i = 0; i < a.size(); ++i) {
    for (int j = i; j < a.size(); ++j) {
      aa.emplace(a.substr(i, j - i + 1));
    }
  }
  for (int i = 0; i < b.size(); ++i) {
    for (int j = i; j < b.size(); ++j) {
      bb.emplace(b.substr(i, j - i + 1));
    }
  }
  vector<string> un;
  for (auto &aaa : aa) {
    if (bb.contains(aaa)) {
      un.emplace_back(aaa);
    }
  }
  assert(0 < k && k <= un.size());
  out << un[k - 1] << '\n';
}

bool is_multi = false;

int main() {
  ifstream in(constants::DATA_IN);
  ofstream out(constants::SLOW_OUT);

  solve(in, out);

  return 0;
}
