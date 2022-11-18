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

#define rep(i, a, b)    for (decltype(a) i = (a); (i) < (b); ++(i))
#define forr(el, cont)  for (auto &(el) : (cont))
#define read(k)         ll k; cin >> k

template<typename T = ll> using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

const ll inf = 1e15;
const ll MOD = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<int> in_deg(n, 0);
    rep(_, 0, m) {
        int a, b;
        cin >> a >> b;

        adj[--a].eb(--b);
        ++in_deg[b];
    }

    queue<int> q;
    vector<int> p(n, -1);
    vector<ll> dist(n, -inf);
    rep(v, 0, n) if (in_deg[v] == 0) q.emplace(v);

    dist[0] = 0;
    while (!q.empty()) {
        auto v = q.front(); q.pop();

        for (auto u : adj[v]) {
            if (dist[u] < dist[v] + 1) {
                dist[u] = dist[v] + 1;
                p[u] = v;
            }
            if (--in_deg[u] == 0) q.emplace(u);
        }
    }

    if (dist[n - 1] < 0) { cout << "IMPOSSIBLE"; return; }
    vector<int> path;
    for (auto cur = n - 1; ; cur = p[cur]) {
        path.eb(cur);
        if (path.back() == 0) break;
    }
    reverse(all(path));
    cout << sz(path) << '\n';
    forr(v, path) cout << v + 1 << ' ';
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
