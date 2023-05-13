#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using u64 = ::uint64_t;

u64 to10(string_view s) {
  u64 ans = 0;
  for (auto ch : s) {
    assert(ch == '0' || ch == '1');
    ans <<= 1;
    ans |= ch == '1';
  }
  return ans;
}

void solve() {
  string s; cin >> s;
  u64 n; cin >> n;

  string bits;
  bits.reserve(60);
  for (auto x = n; x > 0;) {
    bits.push_back(char('0' + (x & 1)));
    x >>= 1;
  }

  while (bits.size() < s.size()) bits.push_back('0');
  std::reverse(bits.begin(), bits.end());

  std::reverse(s.begin(), s.end());
  while (s.size() < bits.size()) s.push_back('0');
  std::reverse(s.begin(), s.end());

  assert(bits.size() == s.size());
  bool is_eq = true;
  dbg(s, bits);
  vector<int> qs;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == '?') {
      qs.emplace_back(i);
    }
  }
  int q_1 = -1;
  for (int i = 0; i < bits.size(); ++i) {
    if (bits[i] == s[i]) continue;
    if (is_eq) {
      if (s[i] == '?') {
        s[i] = bits[i];
        if (s[i] == '1') {
          q_1 = i;
        }
      } else if (s[i] > bits[i]) {
        if (q_1 == -1) {
          cout << -1;
          return;
        }
        s[q_1] = '0';
        for (auto j : qs) {
          if (j > q_1) {
            s[j] = '1';
          }
        }
        cout << to10(s) << '\n';
        return;
      } else {
        assert(s[i] < bits[i]);
        is_eq = false;
      }
    } else if (s[i] == '?') {
      s[i] = '1';
    }
  }
  cout << to10(s) << '\n';
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
