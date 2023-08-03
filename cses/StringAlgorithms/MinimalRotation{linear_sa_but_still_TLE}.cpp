
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

template <char MIN_ALPHA = 'a', char MAX_ALPHA = 'z'>
vector<int> suffix_array(string_view s) {
  assert(all_of(s.begin(), s.end(), [](char ch) { return clamp(ch, MIN_ALPHA, MAX_ALPHA) == ch; }));

  const auto n = static_cast<int>(s.size());
  const auto nn = max(MAX_ALPHA - MIN_ALPHA + 1, n) + 1;
  vector<int> sa(n), c(n), cnt(nn, 0);
  for (auto ch : s) {
    ++cnt[ch - MIN_ALPHA];
  }
  for (int i = 1; i < nn; ++i) {
    cnt[i] += cnt[i - 1];
  }
  for (int i = 0; i < n; ++i) {
    sa[--cnt[s[i] - MIN_ALPHA]] = i;
  }
  c[sa[0]] = 0;
  for (int i = 1; i < n; ++i) {
    c[sa[i]] = c[sa[i - 1]] + (s[sa[i - 1]] != s[sa[i]]);
  }

  vector<int> nsa(n), nc(n);
  for (int k = 1; k < n; k <<= 1) {
    for (int i = 0; i < n; ++i) {
      nsa[i] = (sa[i] + n - k) % n;
    }
    fill(cnt.begin(), cnt.end(), 0);
    for (int i = 0; i < n; ++i) {
      ++cnt[c[nsa[i]]];
    }
    for (int i = 1; i < nn; ++i) {
      cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
      sa[--cnt[c[nsa[i]]]] = nsa[i];
    }
    nc[sa[0]] = 0;
    for (int i = 1; i < n; ++i) {
      auto cur = pair(c[sa[i]], c[(sa[i] + k) % n]);
      auto prv = pair(c[sa[i - 1]], c[(sa[i - 1] + k) % n]);
      nc[sa[i]] = nc[sa[i - 1]] + (cur != prv);
    }
    nc.swap(c);
  }

  return sa;
}

void solve() {
  string s;
  cin >> s;

  const auto n = int(s.size());
  auto sa = suffix_array(s);
  dbg(sa);
  int k = sa[0];
  vector<bool> seen(n, false);
  seen[k] = true;
  for (;;) {
    auto nk = (k + n - 1) % n;
    if (seen[nk] || s[sa[0]] != s[nk]) {
      break;
    }
    seen[nk] = true;
    k = nk;
  }
  for (int i = k; i < n; ++i) {
    cout << s[i];
  }
  for (int i = 0; i < k; ++i) {
    cout << s[i];
  }
  cout << '\n';
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
