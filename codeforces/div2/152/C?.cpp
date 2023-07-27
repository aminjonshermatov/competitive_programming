#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  string s; cin >> s;

  vector<int> zeros(n, 0), ones(n);
  zeros[0] = s[0] == '0';
  ones[0] = s[0] == '1';
  for (int i = 1; i < n; ++i) {
    zeros[i] = zeros[i - 1] + (s[i] == '0');
    ones[i] = ones[i - 1] + (s[i] == '1');
  }
  auto sm = [&](vector<int> &prf, int l, int r) -> int {
    return prf[r] - (l > 0 ? prf[l - 1] : 0);
  };

  vector<int> prev_0(n, -1), prev_1(n, -1), next_0(n, -1), next_1(n, -1);
  for (int i = 0; i + 1 < n; ++i) {
    prev_0[i + 1] = s[i] == '0' ? i : prev_0[i];
    prev_1[i + 1] = s[i] == '1' ? i : prev_1[i];
  }
  for (int i = n - 1; i > 0; --i) {
    next_0[i - 1] = s[i] == '0' ? i : next_0[i];
    next_1[i - 1] = s[i] == '1' ? i : next_1[i];
  }

  auto is_pal = [&](int l, int r) {
    for (; l < r; ++l, --r) {
      if (s[l] != s[r]) return false;
    }
    return true;
  };

  set<tuple<int, int, int>> seen;
  int ans = 0;
  bool need_add = true;
  for (int i = 0; i < m; ++i) {
    int l, r; cin >> l >> r;
    --l, --r;
    auto zs = sm(zeros, l, r);
    auto os = sm(ones, l, r);

    if (zs == sm(zeros, l, l + zs) && os == sm(ones, l + zs, r)) {
      ans += need_add;
      need_add = false;
      continue;
    }

    if (zs == 0 || os == 0 || is_pal(l, r)) {
      dbg(l, r, need_add);
      ans += need_add;
      need_add = false;
      continue;
    }

    int start, zz, oo;
    if (zs > 0 && os > 0) {
      if (prev_1[l] == -1) {
        start = 0;
        zz = zs + l;
      } else {
        start = prev_1[l] + 1;
        zz = zs + l - prev_1[l] - 1;
      }

      if (next_0[r] == -1) {
        oo = os + n - r - 1;
      } else {
        oo = os + next_0[r] - r - 1;
      }
    } else if (zs > 0) {
      if (prev_1[l] == -1) {
        start = 0;
        zz = l + zs;
      } else {
        start = prev_1[l] + 1;
        zz = zs + l - prev_1[l] - 1;
      }
      if (next_1[r] == -1) {
        oo = 0;
        zz += n - r - 1;
      } else {
        int ll = next_1[r];
        zz += ll - r - 1;
        int rr;
        if (next_0[ll] == -1) {
          rr = n;
        } else {
          rr = next_0[ll];
        }
        oo = rr - ll;
      }

    } else if (os > 0) {
      zz = 0;
      if (prev_0[l] == -1) {
        start = 0;
        oo = os + l;
      } else {
        start = prev_0[l] + 1;
        oo = os + l - prev_0[l] - 1;
      }
      if (next_0[r] == -1) {
        oo += n - r - 1;
      } else {
        oo += next_0[r] - r - 1;
      }
    } else {
      assert(false);
    }
    dbg(l, r, start, zz, oo);
    auto cur = tuple(start, zz, oo);
    if (seen.count(cur) == 0) {
      ++ans;
      seen.emplace(cur);
    }
  }
  dbg();
  cout << ans << '\n';
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}