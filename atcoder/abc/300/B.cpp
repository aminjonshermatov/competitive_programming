// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int h, w; cin >> h >> w;
  vector<string> A(h), B(h);
  for (auto &r : A) cin >> r;
  for (auto &r : B) cin >> r;

  auto shift_v = [&]() -> void {
    for (int j = 0; j < w; ++j) {
      auto fst = A[0][j];
      for (int i = 0; i + 1 < h; ++i) {
        A[i][j] = A[i + 1][j];
      }
      A[h - 1][j] = fst;
    }
  };
  auto shift_h = [&]() -> void {
    for (int i = 0; i < h; ++i) {
      auto fst = A[i][0];
      for (int j = 0; j + 1 < w; ++j) {
        A[i][j] = A[i][j + 1];
      }
      A[i][w - 1] = fst;
    }
  };

  auto ok = [&]() -> bool {
    for (int i = 0; i < h; ++i) {
      if (A[i] != B[i]) return false;
    }
    return true;
  };

  auto AA = A;
  auto BB = B;
  for (int s = 0; s < h; ++s) {
    for (int t = 0; t < w; ++t) {
      A = AA;
      B = BB;
      for (int _ = 0; _ < s; ++_) shift_v();
      for (int _ = 0; _ < t; ++_) shift_h();
      if (ok()) {
        cout << "Yes\n";
        return;
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
