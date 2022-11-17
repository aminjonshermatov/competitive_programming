#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long double ld;

#define fi first
#define se second
#define P pair
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (ll)((x).size())

#define rep(i, a, b) for (ll i = (a); (i) < (b); ++(i))
#define forr(el, cont) for (auto &(el) : (cont))
#define read(k) ll k; cin >> k

#define IOS ios_base::sync_with_stdio(false); \
            cin.tie(nullptr);                 \
            cout.tie(nullptr);

template<typename T>
using V = vector<T>;

template<typename T = ll>
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

[[maybe_unused]] mt19937 rnd(143);

const ll inf = 1e15;
const ll MOD = 1e9 + 7;
[[maybe_unused]] const ld pi = atan2(0, -1);
const ld eps = 1e-6;

// ========================================= PROBLEM =========================================

void solve() {
    int n, m;
    cin >> n >> m;

    V<V<pll>> G(n);
    rep(_, 0, m) {
        ll a, b, w;
        cin >> a >> b >> w;
        --a, --b;

        G[a].eb(b, w);
    }

    struct flight_t {
        ll endpoint;
        ll price;
        bool is_used_d;
        bool operator<(const flight_t &other) const { return price > other.price; }
        flight_t(ll e, ll p, bool u) : endpoint(e), price(p), is_used_d(u) { }
    };

    priority_queue<flight_t> pq;
    V<array<ll, 2>> dist(n, {inf, inf});
    dist[0][0] = dist[0][0] = 0;
    pq.emplace(0, 0, false);

    while (!pq.empty()) {
        auto [v, p, used] = pq.top(); pq.pop();

        if (p != dist[v][used]) continue;
        for (auto [u, w] : G[v]) {
            if (!used) {
                ll new_p = p + w / 2;
                if (new_p < dist[u][1]) {
                    dist[u][1] = new_p;
                    pq.emplace(u, new_p, true);
                }
            }

            if (p + w < dist[u][used]) {
                dist[u][used] = p + w;
                pq.emplace(u, dist[u][used], used);
            }
        }
    }

    cout << dist[n - 1][1];
}

bool is_multi = false;

int main() {
    // auto start = chrono::steady_clock::now();

    IOS

    int T = 1;
    if (is_multi) cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        // cout << "Case #" << tc << ": ";
        solve();
        cout << '\n';
    }

    // auto finish = chrono::steady_clock::now();
    // auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    // cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";

    return 0;
}
