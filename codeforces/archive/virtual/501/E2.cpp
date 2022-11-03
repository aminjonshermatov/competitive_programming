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

ll N, M;
V<string> A;
const ll nax = 1001;
int dp_l[nax][nax], dp_r[nax][nax], dp_t[nax][nax], dp_b[nax][nax];

void solve() {
    cin >> N >> M;
    A.resize(N);
    forr(a, A) cin >> a;

    for (auto &it : {dp_l, dp_r, dp_t, dp_b}) memset(it, 0, sizeof(dp_l));

    rep(i, 0, N) {
        if (A[i][0] == '*') dp_l[i][0] = 1;
        if (A[i][M - 1] == '*') dp_r[i][M - 1] = 1;
    }

    rep(j, 0, M) {
        if (A[0][j] == '*') dp_t[0][j] = 1;
        if (A[N - 1][j] == '*') dp_b[N - 1][j] = 1;
    }

    rep(i, 0, N) rep(j, 1, M) if (A[i][j] == '*') dp_l[i][j] += dp_l[i][j - 1] + 1;
    rep(i, 0, N) for (ll j = M - 2; j >= 0; --j) if (A[i][j] == '*') dp_r[i][j] += dp_r[i][j + 1] + 1;
    rep(j, 0, M) rep(i, 1, N) if (A[i][j] == '*') dp_t[i][j] += dp_t[i - 1][j] + 1;
    rep(j, 0, M) for (ll i = N - 2; i >= 0; --i) if (A[i][j] == '*') dp_b[i][j] += dp_b[i + 1][j] + 1;

//    for (auto &it : {dp_l, dp_r, dp_t, dp_b}) {
//        rep(i, 0, N) {
//            rep(j, 0, M) cout << it[i][j] << " \n"[j + 1 == M];
//        }
//        cout << '\n';
//    }

    V<tuple<ll, ll, ll>> ans;
    rep(i, 1, N - 1) {
        rep(j, 1, M - 1) {
            if (A[i][j] == '*' || A[i][j] == '#') {
                auto mn = min({dp_l[i][j - 1], dp_r[i][j + 1], dp_t[i - 1][j], dp_b[i + 1][j]});
                if (mn > 0) {
                    for (ll k = mn; k >= 0; --k) A[i][j - k] = A[i][j + k] = A[i - k][j] = A[i + k][j] = '#';
                    ans.emplace_back(i + 1, j + 1, mn);
                }
            }
        }
    }

    rep(i, 0, N) {
        rep(j, 0, M) {
            if (A[i][j] == '*') { cout << -1; return; }
        }
    }

    cout << sz(ans) << '\n';
    forr(a, ans) cout << get<0>(a) << ' ' << get<1>(a) << ' ' << get<2>(a) << '\n';
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
