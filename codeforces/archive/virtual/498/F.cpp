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
typedef unsigned long long ull;
typedef long double ld;

#define F first
#define S second
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

inline constexpr array<ll, 4> dy = {1, 0, -1, 0};
inline constexpr array<ll, 4> dx = {0, 1, 0, -1};

void solve() {
    ll N, M, K;
    cin >> N >> M >> K;

    auto isSafe = [&](ll i, ll j) { return i >= 0 && i < N && j >= 0 && j < M; };

    V<V<ull>> A(N, V<ull>(M));
    forr(r, A) forr(a, r) cin >> a;

    if (N == 1 && M == 1) { cout << (A[0][0] == K); return; }

    V<V<map<ull, ll>>> cnt(N, V<map<ull, ll>>(M));

    auto dfs1 = [&](const auto &self, ll i, ll j, ull a, ll c) -> void {
        if (c == 0) {
            ++cnt[i][j][a];
            return;
        }

        rep(k, 0, 2) {
            ll ii = i + dy[k], jj = j + dx[k];
            if (isSafe(ii, jj)) {
                self(self, ii, jj, a ^ A[ii][jj], c - 1);
            }
        }
    };

    ll ans = 0;
    auto dfs2 = [&](const auto &self, ll i, ll j, ull a, ll c) -> void {
        if (c == 0) {
            ans += cnt[i][j][K ^ a];
            return;
        }

        rep(k, 2, 4) {
            ll ii = i + dy[k], jj = j + dx[k];
            if (isSafe(ii, jj)) {
                self(self, ii, jj, c > 1 ? a ^ A[ii][jj] : a, c - 1);
            }
        }
    };

    ll h = (N + M - 2) >> 1;
    dfs1(dfs1, 0, 0, A[0][0], h);
    dfs2(dfs2, N - 1, M - 1, A[N - 1][M - 1], N + M - 2 - h);

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
