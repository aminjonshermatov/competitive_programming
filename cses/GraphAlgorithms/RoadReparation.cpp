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

template<typename T = ll> using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

const ll inf = 1e15;
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

void solve() {
    int n, m;
    cin >> n >> m;

    using edge_t = tuple<int, int, int>;
    vector<edge_t> edges(m);
    rep(i, 0, m) {
        int a, b, w;
        cin >> a >> b >> w;

        --a, --b;
        edges.eb(w, a, b);
        edges.eb(w, b, a);
    }

    sort(all(edges));
    DSU dsu(n);
    ll ans = 0;
    for (auto [w, f, t] : edges) {
        if (dsu.is_same(f ,t)) continue;
        dsu.merge(f ,t);
        ans += w;
    }

    set<int> comp;
    rep(v, 0, n) comp.insert(dsu.find(v));
    if (sz(comp) > 1) { cout << "IMPOSSIBLE"; return; }
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
