#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int ha, wa; cin >> ha >> wa;
  vector<string> A(ha);
  for (auto &a : A) cin >> a;
  int hb, wb; cin >> hb >> wb;
  vector<string> B(hb);
  for (auto &b : B) cin >> b;
  int hx, wx; cin >> hx >> wx;
  vector<string> X(hx);
  for (auto &x : X) cin >> x;

  int H = ha + hb + hx;
  int W = wa + wb + wx;
  vector<vector<char>> ng(H, vector<char>(W));
  auto print = [&](vector<string> &g, int I, int J) -> void {
    assert(I + g.size() < H);
    assert(J + g[0].size() < W);
    for (int i = 0; i < g.size(); ++i) {
      for (int j = 0; j < g[0].size(); ++j) {
        ng[i + I][j + J] = g[i][j];
      }
    }
  };
  auto is_same = [&](int I, int J) -> bool {
    assert(hx + I < H);
    assert(wx + J < W);
    for (int i = 0; i < H; ++i) {
      for (int j = 0; j < W; ++j) {
        if (i >= I && i - I + 1 <= hx && j >= J && j - J + 1 <= wx) {
          if (ng[i][j] != X[i - I][j - J]) {
            return false;
          }
        } else {
          if (ng[i][j] == '#') {
            return false;
          }
        }
      }
    }
    return true;
  };
  auto clear = [&]() -> void {
    for (auto &r : ng) {
      fill(r.begin(), r.end(), '.');
    }
  };
  for (int ai = 0; ai + ha < H; ++ai) {
    for (int aj = 0; aj + wa < W; ++aj) {

      for (int bi = 0; bi + hb < H; ++bi) {
        for (int bj = 0; bj + wb < W; ++bj) {
          clear();
          print(A, ai, aj);
          print(B, bi, bj);

          for (int xi = 0; xi + hx < H; ++xi) {
            for (int xj = 0; xj + wx < W; ++xj) {
              if (is_same(xi, xj)) {
                cout << "Yes\n";
                return;
              }
            }
          }
        }
      }
    }
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
