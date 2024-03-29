#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

constexpr auto inf = numeric_limits<i64>::max();

void solve() {
  int n, k; cin >> n >> k;
  vector<int> as(n);
  for (auto &a : as) cin >> a;

  struct Node {
    int id = -1;
    Node *go[2]{nullptr, nullptr};
  };

  Node root = Node();
  auto add = [&](int id) -> void {
    auto cur = &root;
    for (int ib = k - 1; ib >= 0; --ib) {
      if (cur->go[as[id] >> ib & 1] == nullptr) {
        cur->go[as[id] >> ib & 1] = new Node();
      }
      cur = cur->go[as[id] >> ib & 1];
    }
    cur->id = id;
  };

  auto get = [&](int x) -> pair<int, int> {
    auto cur = &root;
    int id = -1, nx = 0;
    for (int ib = k - 1; ib >= 0; --ib) {
      int b = x >> ib & 1;
      if (cur->go[b] != nullptr) {
        if (b == 0) {
          nx |= 1 << ib;
        }
        cur = cur->go[b];
      } else if (cur->go[b ^ 1] != nullptr) {
        cur = cur->go[b ^ 1];
      } else {
        id = cur->id;
        break;
      }
    }
    if (id == -1) {
      assert(cur != nullptr);
      id = cur->id;
    }
    return {id, nx};
  };

  array<int, 3> ans{};
  ans.fill(-1);
  int mx_f = -1;
  for (int i = 0; i < n; ++i) {
    auto [j, x] = get(as[i]);
    if (j != -1) {
      auto nf = ((as[j] ^ x) & (as[i] ^ x));
      if (nf > mx_f) {
        mx_f = nf;
        ans[0] = j + 1;
        ans[1] = i + 1;
        ans[2] = x;
      }
    }
    add(i);
  }
  for (auto x : ans) {
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
