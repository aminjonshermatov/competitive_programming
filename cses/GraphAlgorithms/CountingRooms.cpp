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

inline constexpr array<int, 5> dk = {1, 0, -1, 0, 1};

void solve() {
    int n, m;
    cin >> n >> m;
    V<string> M(n);
    forr(r, M) cin >> r;

    auto is_safe = [&](int i, int j) { return i >= 0 && i < n && j >= 0 && j < m; };

    queue<pii> q;
    int ans = 0;
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (M[i][j] != '#') {
                ++ans;
                q.emplace(i, j);
                while (!q.empty()) {
                    auto [y, x] = q.front(); q.pop();

                    rep(k, 0, 4) {
                        int yy = y + dk[k];
                        int xx = x + dk[k + 1];
                        if (is_safe(yy, xx) && M[yy][xx] != '#') {
                            M[yy][xx] = '#';
                            q.emplace(yy, xx);
                        }
                    }
                }
            }
        }
    }

    cout << ans;
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
