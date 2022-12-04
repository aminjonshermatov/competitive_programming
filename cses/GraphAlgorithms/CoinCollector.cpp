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

#define rep(i, a, b)    for (auto i = (a); (i) < (b); ++(i))
#define forr(el, cont)  for (auto &(el) : (cont))
#define read(k)         ll k; cin >> k

template<typename T>             using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename K, typename V> using gp_ht = gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>, linear_probe_fn<>, hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<>, true>>;

const ll inf = 1e15;
const ll MOD = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

void solve() {
    int n, m; cin >> n >> m;

    vector<int> C(n);
    forr(c, C) cin >> c;

    vector<vector<int>> g(n), gr(n);
    rep(_, 0, m) {
        int a, b; cin >> a >> b;
        --a, --b;

        g[a].eb(b);
        gr[b].eb(a);
    }

    vector<bool> used(n, false);
    vector<int> order;
    order.reserve(n);

    auto top_sort = [&](auto self, int v) -> void {
        used[v] = true;
        forr(u, g[v]) if (!used[u]) self(self, u);
        order.eb(v);
    };
    rep(v, 0, n) if (!used[v]) top_sort(top_sort, v);

    vector<int> comp(n);
    auto dfs = [&](auto self, int v, int c) -> void {
        used[v] = true;
        comp[v] = c;
        forr(u, gr[v]) if (!used[u]) self(self, u, c);
    };

    reverse(all(order));
    fill(all(used), false);
    int comp_sz = 0;
    forr(v, order) if (!used[v]) dfs(dfs, v, comp_sz++);

    vector<ll> group_sum(comp_sz, 0ll);
    vector<vector<int>> g_scc(comp_sz);
    rep(v, 0, n) {
        group_sum[comp[v]] += C[v];
        forr(u, g[v]) if (comp[v] != comp[u]) g_scc[comp[v]].eb(comp[u]);
    }

    vector<ll> memo(comp_sz, -1);
    auto dp = [&](auto &self, int comp_v) -> ll {
        ll &res = memo[comp_v];
        if (res != -1) return res;

        res = 0;
        forr(comp_u, g_scc[comp_v]) res = max(res, self(self, comp_u));
        res += group_sum[comp_v];
        return res;
    };

    ll ans = 0;
    rep(comp_v, 0, comp_sz) ans = max(ans, dp(dp, comp_v));
    cout << ans;
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
