#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  constexpr int n = 4;
  using T = array<string, n>;
  array<T, 3> gs{};
  for (auto &g : gs) {
    for (auto &r : g) {
      cin >> r;
    }
  }

  const auto rot = [&](T &m) -> void {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        auto temp = m[i][j];
        m[i][j] = m[j][i];
        m[j][i] = temp;
      }
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n / 2; ++j) {
        auto temp = m[i][j];
        m[i][j] = m[i][n - j - 1];
        m[i][n - j - 1] = temp;
      }
    }
  };

  for (int r1 = 0; r1 < n; ++r1) {
    for (int r2 = 0; r2 < n; ++r2) {
      for (int r3 = 0; r3 < n; ++r3) {
        for (int i1 = -n + 1; i1 < n; ++i1) {
          for (int j1 = -n + 1; j1 < n; ++j1) {
            for (int i2 = -n + 1; i2 < n; ++i2) {
              for (int j2 = -n + 1; j2 < n; ++j2) {
                for (int i3 = -n + 1; i3 < n; ++i3) {
                  for (int j3 = -n + 1; j3 < n; ++j3) {
                    T cur{};
                    for (auto &r : cur) {
                      r.assign(4, '#');
                    }
                    bool ok = true;
                    const auto run = [&](T &g, int io, int jo) -> void {
                      for (int i = 0; i < n && ok; ++i) {
                        for (int j = 0; j < n && ok; ++j) {
                          if (g[i][j] == '#') {
                            if (clamp(io + i, 0, n - 1) != io + i || clamp(jo + i, 0, n - 1) != jo + i || cur[io + i][jo + j] == '#') {
                              ok = false;
                            } else {
                              cur[io + i][jo + j] = '#';
                            }
                          }
                        }
                      }
                    };
                    run(gs[0], i1, j1);
                    run(gs[1], i2, j2);
                    run(gs[2], i3, j3);
                    for (auto &r : cur) {
                      for (auto c : r) {
                        ok &= c == '#';
                      }
                    }
                    if (ok) {
                      cout << "Yes\n";
                      return;
                    }
                  }
                }
              }
            }
          }
        }
        rot(gs[2]);
      }
      rot(gs[1]);
    }
    rot(gs[0]);
  }
  cout << "No\n";
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
