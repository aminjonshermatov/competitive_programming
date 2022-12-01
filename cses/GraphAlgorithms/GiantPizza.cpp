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

template<typename T>            using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename K,typename V> using gp_ht = gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>, linear_probe_fn<>, hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<>, true>>;

const ll inf = 1e15;
const ll MOD = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<ll>> g(2*m + 2), gr(2*m + 2);
    rep(_, 0, n) {
        char a_ok, b_ok;
        ll a, b;
        cin >> a_ok >> a >> b_ok >> b;

        g[2 * a ^ (a_ok == '-') ^ 1].eb(2 * b ^ (b_ok == '-')); // not A -> B
        g[2 * b ^ (b_ok == '-') ^ 1].eb(2 * a ^ (a_ok == '-')); // not B -> A
        gr[2 * b ^ (b_ok == '-')].eb(2 * a ^ (a_ok == '-') ^ 1);
        gr[2 * a ^ (a_ok == '-')].eb(2 * b ^ (b_ok == '-') ^ 1);
    }

    vector<bool> used(2*m + 2, false);
    vector<ll> order;
    auto top_sort = [&](auto &self, ll v) -> void {
        used[v] = true;
        forr(u, g[v]) if (!used[u]) self(self, u);
        order.eb(v);
    };
    rep(v, 1, 2*m + 2) if (!used[v]) top_sort(top_sort, v);

    vector<ll> comp(2*m + 2);
    auto dfs = [&](auto &self, ll v, ll cur_comp) -> void {
        used[v] = true;
        comp[v] = cur_comp;
        forr(u, gr[v]) if (!used[u]) self(self, u, cur_comp);
    };

    reverse(all(order));
    fill(all(used), false);
    ll c = 0;
    forr(v, order) if (!used[v]) dfs(dfs, v, ++c);

    vector<bool> sat(m, false);
    for (ll v = 1; v <= m; ++v) {
        if (comp[v << 1] == comp[(v << 1) | 1]) {
            cout << "IMPOSSIBLE";
            return;
        }
        sat[v - 1] = comp[v << 1] > comp[(v << 1) | 1];
    }

    for (auto ok : sat) cout << (ok ? '+' : '-') << ' ';
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
