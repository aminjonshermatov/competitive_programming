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

#define rep(i, a, b)    for (ll i = (a); (i) < (b); ++(i))
#define forr(el, cont)  for (auto &(el) : (cont))
#define read(k)         ll k; cin >> k

template<typename T = ll> using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

const ll inf = 1e15;
const ll MOD = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pii>> G(n);
    rep(_, 0, m) {
        int a, b, w;
        cin >> a >> b >> w;

        G[--a].eb(--b, w);
    }

    vector<priority_queue<ll>> best(n);
    priority_queue<pli, vector<pli>, greater<>> pq;
    pq.emplace(0, 0);
    best[0].emplace(0);

    while (!pq.empty()) {
        auto [c, v] = pq.top(); pq.pop();
        if (c > best[v].top()) continue;

        for (auto [u, w] : G[v]) {
            if (sz(best[u]) < k) {
                best[u].emplace(c + w);
                pq.emplace(c + w, u);
            } else if (best[u].top() > c + w) {
                best[u].pop();
                best[u].emplace(c + w);
                pq.emplace(c + w, u);
            }
        }
    }

    vector<ll> res;
    res.reserve(k);
    while (!best[n - 1].empty()) {
        res.emplace_back(best[n - 1].top());
        best[n - 1].pop();
    }

    reverse(all(res));
    forr(d, res) cout << d << ' ';
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
