#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void test(int n) {
  vector<int> as(n);
  dbg(as);
  iota(as.begin(), as.end(), 1);
  auto is_p = [](int x) -> bool {
    if (x == 1) return false;
    if (x == 2 || x == 3) return true;
    for (int d = 2; d <= x; ++d) {
      if (x % d == 0) {
        return false;
      }
    }
    return true;
  };
  vector<pair<int, vector<int>>> nums;
  do {
    int cnt = 0;
    for (int l = 0; l < n; ++l) {
      for (int r = l; r < n; ++r) {
        set<int> ss;
        for (int x = 1; x <= n + 1; ++x) {
          ss.insert(x);
        }
        for (int k = l; k <= r; ++k) {
          ss.erase(as[k]);
        }
        assert(!ss.empty());
        cnt += is_p(*ss.begin());
      }
    }
    nums.emplace_back(cnt, as);
  } while (next_permutation(as.begin(), as.end()));
  sort(nums.rbegin(), nums.rend());
  dbg(nums[0].first, nums[0].second);
  for (int i = 1; i < nums.size(); ++i) {
    if (nums[i].first == nums[i - 1].first) {
      dbg(nums[i].first, nums[i].second);
    } else {
      break;
    }
  }
  exit(0);
}

void solve() {
  // test(6);
  int n; cin >> n;
  for (int i = 2; i <= n; i += 2) {
    cout << i << ' ';
  }
  cout << 1 << ' ';
  for (int x = n - (n % 2 == 0); x > 1; x -= 2) {
    cout << x << ' ';
  }
  cout << '\n';
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
