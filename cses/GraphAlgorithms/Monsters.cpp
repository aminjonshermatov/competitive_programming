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

inline constexpr array<tuple<int, int, char>, 4> dir{
    make_tuple(0, -1, 'L'),
    make_tuple(0, +1, 'R'),
    make_tuple(-1, 0, 'U'),
    make_tuple(+1, 0, 'D')
};

const map<char, pii> rev_dir{
    mp('L', mp(0, +1)),
    mp('R', mp(0, -1)),
    mp('U', mp(+1, 0)),
    mp('D', mp(-1, 0))
};

void solve() {
    int n, m;
    cin >> n >> m;

    auto is_safe = [&](int i, int j) -> bool { return i >= 0 && i < n && j >= 0 && j < m; };
    auto is_corner = [&](int i, int j) -> bool { return i == 0 || i + 1 == n || j == 0 || j + 1 == m; };

    V<string> G(n);
    pii start{-1, -1};
    V<V<ll>> dist(n, V<ll>(m, inf));
    queue<pii> q;
    rep(i, 0, n) {
        cin >> G[i];

        rep(j, 0, m) {
            if (start.fi == -1 && G[i][j] == 'A') {
                start = mp(i, j);
                if (is_corner(int(i), int(j))) { cout << "YES\n0"; return; }
            }
            if (G[i][j] == 'M') q.emplace(i, j), dist[i][j] = 0;
        }
    }

    while (!q.empty()) {
        auto [i, j] = q.front(); q.pop();

        for (auto [di, dj, _] : dir) {
            int ii = i + di;
            int jj = j + dj;

            if (is_safe(ii, jj) && G[ii][jj] == '.' && dist[i][j] + 1 < dist[ii][jj]) {
                dist[ii][jj] = dist[i][j] + 1;
                q.emplace(ii, jj);
            }
        }
    }

    V<V<char>> type(n, V<char>(m, '?'));
    q.emplace(start);
    dist[start.fi][start.se] = 0;
    while (!q.empty()) {
        auto [i, j] = q.front(); q.pop();

        if (is_corner(i, j)) {
            pii cur = mp(i, j);
            string path;
            while (cur != start) {
                path.pb(type[cur.fi][cur.se]);
                cur.fi += rev_dir.at(path.back()).fi;
                cur.se += rev_dir.at(path.back()).se;
            }
            reverse(all(path));
            cout << "YES\n" << sz(path) << '\n' << path;
            return;
        }

        for (auto [di, dj, d] : dir) {
            int ii = i + di;
            int jj = j + dj;

            if (is_safe(ii, jj) && G[ii][jj] == '.' && dist[i][j] + 1 < dist[ii][jj]) {
                dist[ii][jj] = dist[i][j] + 1;
                type[ii][jj] = d;
                q.emplace(ii, jj);
            }
        }
    }

    cout << "NO";
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
