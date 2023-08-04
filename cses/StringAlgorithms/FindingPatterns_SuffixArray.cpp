#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

template <size_t ALPHA = 26, char MIN_ALPHA = 'a'>
vector<int> suffix_array(string_view s) {
  assert(all_of(s.begin(), s.end(), [](char ch) { return clamp<char>(ch, MIN_ALPHA, MIN_ALPHA + ALPHA - 1) == ch; }));

  const auto n = static_cast<int>(s.size());
  const auto nn = max<int>(ALPHA, n) + 1;
  vector<int> p(n), c(n), cnt(nn, 0);
  for (auto ch : s) {
    ++cnt[ch - MIN_ALPHA];
  }
  for (int i = 1; i < nn; ++i) {
    cnt[i] += cnt[i - 1];
  }
  for (int i = 0; i < n; ++i) {
    p[--cnt[s[i] - MIN_ALPHA]] = i;
  }
  c[p[0]] = 0;
  for (int i = 1; i < n; ++i) {
    c[p[i]] = c[p[i - 1]] + (s[p[i - 1]] != s[p[i]]);
  }

  vector<int> np(n), nc(n);
  for (int k = 1; k < n; k <<= 1) {
    for (int i = 0; i < n; ++i) {
      np[i] = (p[i] + n - k) % n;
    }
    fill(cnt.begin(), cnt.end(), 0);
    for (int i = 0; i < n; ++i) {
      ++cnt[c[np[i]]];
    }
    for (int i = 1; i < nn; ++i) {
      cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
      p[--cnt[c[np[i]]]] = np[i];
    }
    nc[p[0]] = 0;
    for (int i = 1; i < n; ++i) {
      auto cur = pair(c[p[i]], c[(p[i] + k) % n]);
      auto prv = pair(c[p[i - 1]], c[(p[i - 1] + k) % n]);
      nc[p[i]] = nc[p[i - 1]] + (cur != prv);
    }
    nc.swap(c);
  }

  return p;
}

void solve() {
  string t; cin >> t;
  t.push_back('a' - 1);
  const auto n = int(t.size());
  const auto sa = suffix_array<27, 'a' - 1>(t);

  int q; cin >> q;
  for (int _ = 0; _ < q; ++_) {
    string s; cin >> s;
    const auto m = int(s.size());

    auto ge = [&](int id) -> bool {
      for (int i = 0; i < m; ++i) {
        if (sa[id] + i >= n) {
          return false;
        }
        if (s[i] != t[sa[id] + i]) {
          return s[i] < t[sa[id] + i];
        }
      }
      return true;
    };

    int lo = -1, hi = n - 1;
    while (hi - lo > 1) {
      auto mid = lo + (hi - lo) / 2;
      (ge(mid) ? hi : lo) = mid;
    }
    bool ok = true;
    for (int i = 0; i < m && ok; ++i) {
      ok &= sa[hi] + i < n && s[i] == t[sa[hi] + i];
    }
    cout << (ok ? "YES" : "NO") << '\n';
  }
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
