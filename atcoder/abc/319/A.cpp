#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  map<string, int> X{
    {"tourist", 3858},{"ksun48", 3679},
            {"Benq", 3658}, {"Um_nik", 3648}, {"apiad", 3638},
            {"Stonefeang", 3630}, {"ecnerwala", 3613}, {"mnbvmar", 3555}, {"newbiedmy", 3516}, { "semiexp", 3481 }
  };
  string s;
  cin >> s;
  cout << X[s] << '\n';
}

bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
