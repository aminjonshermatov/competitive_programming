//
// Created by aminjon on 8/3/23.
//
#include <bits/stdc++.h>

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