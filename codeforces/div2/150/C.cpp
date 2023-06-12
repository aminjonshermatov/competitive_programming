#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

#define int long long

struct segtree {

  int size;
  vector<char> tree;

  void init(int n) {
    size = 1;
    while (size < n) size <<= 1;
    tree.assign(2 * size - 1, 'A');
  }

  void set(int i, char v, int x, int lx, int rx) {
    if (rx - lx == 1) {
      tree[x] = v;
      return;
    }

    int m = lx + (rx - lx) / 2;
    if (i < m) set(i, v, 2 * x + 1, lx, m);
    else set(i, v, 2 * x + 2, m, rx);
    tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
  }

  void set(int i, char v) {
    set(i, v, 0, 0, size);
  }

  int find_last_ge(char v, int up, int x, int lx, int rx) {
    if (tree[x] <= v || lx >= up) return -1;
    if (rx - lx == 1) return lx;

    int m = lx + (rx - lx) / 2;
    auto res = find_last_ge(v, up, 2 * x + 2, m, rx);
    if (res == -1) res = find_last_ge(v, up, 2 * x + 1, lx, m);
    return res;
  }

  int find_last_ge(char v, int up) {
    return find_last_ge(v, up, 0, 0, size);
  }

};

void solve() {
  string s; cin >> s;
  const int n(s.size());
  string mx(n, '#');
  mx[n - 1] = s[n - 1];
  for (int i = n - 2; i >= 0; --i) {
    mx[i] = max(mx[i + 1], s[i]);
  }

  segtree sg;
  sg.init(n);
  for (int i = 0; i < n; ++i) {
    sg.set(i, s[i]);
  }

  array<int, 5> vals{1, 10, 100, 1000, 10000};
  vector<int> pf;
  pf.reserve(n);
  vector<array<int, 5>> pff(n, {0,0,0,0,0});
  for (int i = 0; i < n; ++i) {
    auto tmp = vals[s[i] - 'A'];
    pff[i][s[i] - 'A'] = tmp;
    if (i > 0) {
      for (int j = 0; j < 5; ++j) {
        pff[i][j] += pff[i - 1][j];
      }
    }
    if (i + 1 < n && mx[i + 1] > s[i]) tmp *= -1;
    pf.push_back((pf.empty() ? 0 : pf.back()) + tmp);
  }
  int ans = -1e10;
  dbg(mx);
  dbg(pf);
  dbg(pff);

  for (int i = 0; i < n; ++i) {
    for (auto ch = 'A'; ch <= 'E'; ++ch) {
      swap(s[i], ch);
      auto tmp = vals[s[i] - 'A'];
      if (i + 1 < n && mx[i + 1] > s[i]) tmp *= -1;
      int add = pf[n - 1] - pf[i];

      auto ch_mx = s[i];
      if (i + 1 < n) ch_mx = max(ch_mx, mx[i + 1]);
      //dbg(i, string(1, s[i]), string(1, ch), idx);

      auto idx = sg.find_last_ge(ch_mx, i);
      if  (idx == -1) {
        if (i > 0) {
          int up = 0;
          for (int j = ch_mx - 'A'; j < 5; ++j) {
            up += pff[i - 1][j];
          }
          int lo = 0;
          for (int j = 0; j < ch_mx - 'A'; ++j) {
            lo += pff[i - 1][j];
          }
          add += up - lo;
        }
      } else {
        if (i > 0) {
          add += pf[idx];
          int up = 0;
          for (int j = ch_mx - 'A'; j < 5; ++j) {
            up += pff[i - 1][j] - pff[idx][j];
          }
          int lo = 0;
          for (int j = 0; j < ch_mx - 'A'; ++j) {
            lo += pff[i - 1][j] - pff[idx][j];
          }
          add += up - lo;
        }
      }
      if (ans < tmp + add) {
        dbg(i, string(1, s[i]), string(1, ch), tmp, add, tmp + add, idx);
      }
      ans = max(ans, tmp + add);
      swap(s[i], ch);
    }
  }

  cout << ans << '\n';
}

bool is_multi = true;

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
