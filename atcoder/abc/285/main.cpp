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

template<typename T>             using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename K, typename V> using gp_ht = gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>, linear_probe_fn<>, hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<>, true>>;

const ll inf = 1e15;
const ll MOD = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

inline constexpr array<int, 5> dk{1, 0, -1, 0, 1};

void solve() {
    int h, w; cin >> h >> w;
    vector<string> grid(h);
    for (auto &l : grid) cin >> l;

    auto is_safe = [&](int i, int j) -> bool { return clamp(i, 0, h - 1) == i && clamp(j, 0, w - 1) == j; };

    vector<vector<int>> g(h*w);
    rep(i, h) rep(j, w) {
            if (grid[i][j] != '2') continue;
            rep(k, 4) {
                int ni = i + dk[k];
                int nj = j + dk[k + 1];
                if (is_safe(ni, nj) && grid[ni][nj] != '1') g[i*w + j].eb(ni*w + nj);
            }
        }

    vector<bool> used(h*w, false);
    vector<int> mt(h*w, -1);

    auto try_kuhn = [&](auto f, int v) -> bool {
        if (used[v]) return false;
        used[v] = true;
        forr(u, g[v]) if (mt[u] == -1 || f(f, mt[u])) { mt[u] = v; return true; }
        return false;
    };

    rep(i, h) rep(j, w) {
            fill(all(used), false);
            try_kuhn(try_kuhn, i*w + j);
        }

    rep(u, h*w) if (mt[u] != -1) {
            auto [ui, uj] = div(u, w);
            auto [vi, vj] = div(mt[u], w);
            //cout << ui << ' ' << uj << ',' << vi << ' ' << vj << '\n';
            grid[ui][uj] = grid[vi][vj] = '3';
        }
    rep(i, h) rep(j, w) if (grid[i][j] == '2') {
                rep(k, 4) {
                    int ni = i + dk[k];
                    int nj = j + dk[k + 1];
                    if (!is_safe(ni, nj)) continue;
                    if (grid[ni][nj] == '2' || grid[ni][nj] == '?') grid[i][j] = grid[ni][nj] = '3';
                }
            }
    //rep(i, h) cout << grid[i] << '\n';
    rep(i, h) rep(j, w) if (grid[i][j] == '2') {
                cout << "No";
                return;
            }
    cout << "Yes";
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
