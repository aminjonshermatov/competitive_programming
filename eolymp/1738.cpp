// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;
using namespace __gnu_pbds;

typedef long long           ll;
typedef long double         ld;
typedef pair<ll, ll>        pll;
typedef pair<int, int>      pii;
typedef pair<ll, int>       pli;
typedef pair<int, ll>       pil;
typedef unsigned long long  ull;

#define fi      first
#define se      second
#define P       pair
#define mp      make_pair
#define pb      push_back
#define eb      emplace_back
#define all(x)  (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x)   (ll)((x).size())

#define rep(i, b)       for (auto i = 0; (i) < (b); ++(i))
#define forr(el, cont)  for (auto &(el) : (cont))

template<typename T>             using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename K, typename V> using gp_ht = gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>, linear_probe_fn<>, hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<>, true>>;

const ll inf = 1e15;
const ll MOD = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

inline constexpr array<int, 5> dk{1, 0, -1, 0, 1};

void solve() {
    int n, m, a, b; cin >> n >> m >> a >> b;
    vector<string> grid(n);
    forr(s, grid) cin >> s;

    auto is_safe = [&](int i, int j) { return i >= 0 && i < n && j >= 0 && j < m; };

    int empty = 0;
    vector<vector<int>> g(n*m);
    rep(i, n) {
        rep(j, m) {
            if (grid[i][j] != '*') continue;
            ++empty;
            if ((i + j) & 1) continue;
            rep(k, 4) {
                int ii = i + dk[k];
                int jj = j + dk[k + 1];
                if (is_safe(ii, jj) && grid[ii][jj] == '*') g[i * m + j].eb(ii * m + jj);
            }
        }
    }

    if (2*b <= a) {
        cout << empty*b;
        return;
    }

    vector<bool> used(n*m, false);
    vector<int> mt(n*m, -1);

    auto try_kuhn = [&](auto self, int v) -> bool {
        if (used[v]) return false;
        used[v] = true;
        forr(u, g[v]) {
            if (mt[u] == -1 || self(self, mt[u])) {
                mt[u] = v;
                return true;
            }
        }
        return false;
    };

    rep(i, n) rep(j, m) {
        if ((i + j) & 1) continue;
        fill(all(used), false);
        try_kuhn(try_kuhn, i*m+j);
    }

    int big = 0;
    rep(i, n*m) big += mt[i] != -1;

    cout << big*a + (empty - 2*big)*b;
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
