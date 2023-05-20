#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr string_view snuke{"snuke"};

void solve() {
  int h, w; cin >> h >> w;
  vector<string> g(h);
  for (auto &r : g) cin >> r;

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      bool ok1 = (i + 4) < h;
      for (int k = 0; k < snuke.size() && ok1; ++k) {
        ok1 &= g[i + k][j] == snuke[k];
      }
      if (ok1) {
        for (int k = 0; k < snuke.size(); ++k) {
          cout << i + k + 1 << ' ' << j + 1 << '\n';
        }
        return;
      }
      bool ok2 = (i + 1) >= snuke.size();
      for (int k = 0; k < snuke.size() && ok2; ++k) {
        ok2 &= g[i - k][j] == snuke[k];
      }
      if (ok2) {
        for (int k = 0; k < snuke.size(); ++k) {
          cout << i - k + 1 << ' ' << j + 1 << '\n';
        }
        return;
      }
    }
  }

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      bool ok1 = (j + 4) < w;
      for (int k = 0; k < snuke.size() && ok1; ++k) {
        ok1 &= g[i][j + k] == snuke[k];
      }
      if (ok1) {
        for (int k = 0; k < snuke.size(); ++k) {
          cout << i + 1 << ' ' << j + k + 1 << '\n';
        }
        return;
      }
      bool ok2 = (j + 1) >= snuke.size();
      for (int k = 0; k < snuke.size() && ok2; ++k) {
        ok2 &= g[i][j - k] == snuke[k];
      }
      if (ok2) {
        for (int k = 0; k < snuke.size(); ++k) {
          cout << i + 1 << ' ' << j - k + 1 << '\n';
        }
        return;
      }
    }
  }

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      bool ok1 = (j + 4) < w && (i + 4) < h;
      for (int k = 0; k < snuke.size() && ok1; ++k) {
        ok1 &= g[i + k][j + k] == snuke[k];
      }
      if (ok1) {
        for (int k = 0; k < snuke.size(); ++k) {
          cout << i + k + 1 << ' ' << j + k + 1 << '\n';
        }
        return;
      }
      bool ok2 = (j + 1) >= snuke.size() && (i + 1) >= snuke.size();
      for (int k = 0; k < snuke.size() && ok2; ++k) {
        ok2 &= g[i - k][j - k] == snuke[k];
      }
      if (ok2) {
        for (int k = 0; k < snuke.size(); ++k) {
          cout << i - k + 1 << ' ' << j - k + 1 << '\n';
        }
        return;
      }
    }
  }

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      bool ok1 = (j + 4) < w && (i + 1) >= snuke.size();
      for (int k = 0; k < snuke.size() && ok1; ++k) {
        ok1 &= g[i - k][j + k] == snuke[k];
      }
      if (ok1) {
        for (int k = 0; k < snuke.size(); ++k) {
          cout << i - k + 1 << ' ' << j + k + 1 << '\n';
        }
        return;
      }
      bool ok2 = (j + 1) >= snuke.size() && (i + 4) < h;
      for (int k = 0; k < snuke.size() && ok2; ++k) {
        ok2 &= g[i + k][j - k] == snuke[k];
      }
      if (ok2) {
        for (int k = 0; k < snuke.size(); ++k) {
          cout << i + k + 1 << ' ' << j - k + 1 << '\n';
        }
        return;
      }
    }
  }
  assert(false);
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
