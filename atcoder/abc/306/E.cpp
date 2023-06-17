#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

using i64 = int64_t;

void solve() {
  int n, k, q; cin >> n >> k >> q;
  vector<i64> nums(n, 0);
  ordered_set<i64> os(nums.begin(), nums.end());

  i64 sm = 0;
  int sz = k;
  while (q--) {
    int x;
    i64 y;
    cin >> x >> y;
    --x;
    auto ord = os.order_of_key(nums[x]);
    if (ord >= n - k) {
      sm -= nums[x];
      --sz;
    }
    dbg(ord, sm, sz);
    os.erase(os.find_by_order(ord));

    nums[x] = y;
    os.insert(nums[x]);
    ord = os.order_of_key(nums[x]);
    if (ord >= n - sz) {
      if (n > sz) {
        sm -= *os.find_by_order(n - sz - 1);
        --sz;
      }
      sm += nums[x];
      ++sz;
    }
    if (sz < k) {
      assert(sz + 1 == k);
      sm += *os.find_by_order(n - k);
      ++sz;
    }
    dbg(nums, os, ord, sm);
    cout << sm << '\n';
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
