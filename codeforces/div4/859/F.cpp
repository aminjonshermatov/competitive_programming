// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<int, ll> pil;
typedef unsigned long long ull;

#define fi first
#define se second
#define P pair
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (ll)(x.size())

#define rep(i, b) for (auto i = 0; i < b; ++i)
#define forr(el, cont) for (auto &el: cont)

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename K, typename V>
using gp_ht = gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>, linear_probe_fn<>, hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<>, true>>;

inline constexpr auto inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();
inline constexpr int MOD = 1e9 + 7;
inline const ld pi = ::atan2(0, -1);
inline constexpr ld eps = 1e-6;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

struct Point2d {
  int x, y;
  bool operator<(const Point2d &other) const {
    if (y != other.y) return y < other.y;
    return x < other.x;
  }
};

struct Dir {
  int dy, dx, id;
};

array<Dir, 4> dirs {{
        {+1, +1, 0}, // DR
        {+1, -1, 1}, // DL
        {-1, -1, 2}, // UL
        {-1, +1, 3}  // UR
}};

void solve() {
  int n, m;
  cin >> n >> m;
  Point2d start{}, finish{};
  cin >> start.y >> start.x >> finish.y >> finish.x;

  auto ok = [&](int x, int y) -> bool {
    return clamp(x, 1, m) == x && clamp(y, 1, n) == y;
  };

  queue<pair<Point2d, int>> q;
  string D; cin >> D;
  int dd;
  if (D == "DR") dd = 0;
  else if (D == "DL") dd = 1;
  else if (D == "UL") dd = 2;
  else if (D == "UR") dd = 3;
  else assert(false);
  vector<vector<vector<int>>> dist(n + 1, vector<vector<int>>(m + 1, vector<int>(4, inf)));
  q.emplace(start, dd);
  dist[start.y][start.x][dd] = 0;
  auto cur = start;
  int cur_d = dd;
  //cout << "cur " << cur.y << ' ' << cur.x << ' ' << cur_d << endl;
  while (true) {
    auto nx = cur.x + dirs[cur_d].dx;
    auto ny = cur.y + dirs[cur_d].dy;
    auto ok_x = clamp(nx, 1, m) == nx;
    auto ok_y = clamp(ny, 1, n) == ny;
    if (ok_x && ok_y) {
      //cout << "1" << endl;
      //cout << cur.y << ' ' << cur.x << ' ' << ny << ' ' << nx << ' ' << cur_d << endl;
      if (dist[ny][nx][cur_d] != inf) break ;
      dist[ny][nx][cur_d] = dist[cur.y][cur.x][cur_d];
      cur = Point2d{nx, ny};
    } else if (ok_x && !ok_y) {
      //cout << "2" << endl;
      int nd;
      switch (cur_d) {
        case 0: {
          nd = 3;
          break ;
        }
        case 1: {
          nd = 2;
          break ;
        }
        case 2: {
          nd = 1;
          break ;
        }
        case 3: {
          nd = 0;
          break ;
        }
      }
      nx = cur.x + dirs[nd].dx;
      ny = cur.y + dirs[nd].dy;
      assert(ok(nx, ny));
      if (dist[ny][nx][nd] != inf) break ;
      dist[ny][nx][nd] = dist[cur.y][cur.x][cur_d] + 1;
      cur = Point2d{nx, ny};
      cur_d = nd;
    } else if (!ok_x && ok_y) {
      //cout << "3" << endl;
      int nd;
      switch (cur_d) {
        case 0: {
          nd = 1;
          break ;
        }
        case 1: {
          nd = 0;
          break ;
        }
        case 2: {
          nd = 3;
          break ;
        }
        case 3: {
          nd = 2;
          break ;
        }
      }
      nx = cur.x + dirs[nd].dx;
      ny = cur.y + dirs[nd].dy;
      assert(ok(nx, ny));
      if (dist[ny][nx][nd] != inf) break ;
      dist[ny][nx][nd] = dist[cur.y][cur.x][cur_d] + 1;
      cur = Point2d{nx, ny};
      cur_d = nd;
    } else {
      //cout << "4" << endl;
      int nd;
      switch (cur_d) {
        case 0: {
          nd = 2;
          break ;
        }
        case 1: {
          nd = 3;
          break ;
        }
        case 2: {
          nd = 0;
          break ;
        }
        case 3: {
          nd = 1;
          break ;
        }
      }
      nx = cur.x + dirs[nd].dx;
      ny = cur.y + dirs[nd].dy;
      assert(ok(nx, ny));
      if (dist[ny][nx][nd] != inf) break ;
      dist[ny][nx][nd] = dist[cur.y][cur.x][cur_d] + 1;
      cur = Point2d{nx, ny};
      cur_d = nd;
    }
  }
  int ans = inf;
  rep(k, 4) ans = min(ans, dist[finish.y][finish.x][k]);
  cout << (ans == inf ? -1 : ans) << '\n';
}

//#define MEASURE_TIME
bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#ifdef MEASURE_TIME
  auto start = chrono::steady_clock::now();
#endif
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
#ifdef MEASURE_TIME
  auto finish = chrono::steady_clock::now();
  auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
  cerr << endl
       << "Time: " << elapsed_ms.count() << " ms\n";
#endif
  return 0;
}
