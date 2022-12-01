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
    vector<int> parent, rank, size;
    int max_sz, comp;
public:
    explicit DSU(int n) {
        parent.resize(n);
        iota(all(parent), 0);
        rank.assign(n, 1);
        size.assign(n, 1);
        max_sz = 1;
        comp = n;
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
        size[pv] += size[pu];
        max_sz = max(max_sz, size[pv]);
        --comp;
        if (rank[pv] == rank[pu]) ++rank[pv];
    }

    auto is_same(int v, int u) -> bool { return find(v) == find(u); }
    auto max_size() const -> pii { return mp(comp, max_sz); }
};

void solve() {
    int n, m;
    cin >> n >> m;

    DSU dsu(n);
    rep(_, 0, m) {
        int a, b;
        cin >> a >> b;
        --a, --b;

        if (!dsu.is_same(a, b)) dsu.merge(a, b);
        auto info = dsu.max_size();
        cout << info.fi << ' ' << info.se << '\n';
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
