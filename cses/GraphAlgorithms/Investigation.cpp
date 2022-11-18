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

    vector<vector<pii>> g(n);
    rep(_, 0, m) {
        int a, b, w;
        cin >> a >> b >> w;
        --a, --b;

        g[a].eb(b, w);
    }

    vector<ull> dist(n, inf);
    vector<ull> cnt(n, 0);
    vector<ull> mn(n, 0);
    vector<ull> mx(n, 0);
    dist[0] = 0;
    cnt[0] = 1;
    mn[0] = mx[0] = 0;
    priority_queue<pli, vector<pli>, greater<>> pq;
    pq.emplace(0, 0);

    vector<bool> used(n, false);
    while (!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();
        if (d != dist[v] || used[v]) continue;

        used[v] = true;
        for (auto [u, w] : g[v]) {
            ull new_p = d + w;
            if (new_p < dist[u]) {
                dist[u] = new_p;
                cnt[u] = cnt[v];
                mn[u] = mn[v] + 1;
                mx[u] = mx[v] + 1;
                pq.emplace(new_p, u);
            } else if (new_p == dist[u]) {
                cnt[u] = (cnt[u] + cnt[v]) % MOD;
                mn[u] = min(mn[u], mn[v] + 1);
                mx[u] = max(mx[u], mx[v] + 1);
                pq.emplace(new_p, u);
            }
        }
    }

    cout << dist[n - 1] << ' ' << cnt[n - 1] << ' ' << mn[n - 1] << ' ' << mx[n - 1];
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