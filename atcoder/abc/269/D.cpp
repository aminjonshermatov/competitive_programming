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

#define rep(i, b)    for (auto i = 0; (i) < (b); ++(i))
#define forr(el, cont)  for (auto &(el) : (cont))

template<typename T>             using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename K, typename V> using gp_ht = gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>, linear_probe_fn<>, hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<>, true>>;

const ll inf = 1e9;
const ll MOD = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

class DSU {
    vector<int> parent, rank;
public:
    explicit DSU(int n) {
        parent.resize(n);
        iota(all(parent), 0);
        rank.assign(n, 1);
    }

    auto find(int v) -> int {
        if (parent[v] != v) parent[v] = find(parent[v]);
        return parent[v];
    }

    auto merge(int v, int u) -> void {
        auto pv = find(v);
        auto pu = find(u);
        if (pv == pu) return;

        if (rank[pv] < rank[pu]) swap(pv, pu);
        parent[pu] = pv;
        if (rank[pv] == rank[pu]) ++rank[pv];
    }

    auto is_same(int v, int u) -> bool {
        return find(v) == find(u);
    }
};

array<int, 6> dy{-1,-1,0,0,1,1};
array<int, 6> dx{-1,0,-1,1,0,1};

void solve() {
    int n;
    cin >> n;

    map<pii, int> mm;
    vector<pii> A(n);
    rep(i, n) {
        cin >> A[i].fi >> A[i].se;
        mm[mp(A[i].fi, A[i].se)] = i;
    }

    DSU dsu(n);
    rep(i, n) {
        rep(k, 6) {
            int x = A[i].fi + dx[k];
            int y = A[i].se + dy[k];
            if (auto kv = mp(x, y); mm.count(kv) > 0) dsu.merge(i, mm[mp(x, y)]);
        }
    }

    int ans = 0;
    rep(i, n) ans += (i == dsu.find(i));
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