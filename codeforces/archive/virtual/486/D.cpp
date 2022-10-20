#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

typedef long long ll;
typedef long double ld;

#define F first
#define S second
#define mk make_pair
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

const ll max_n = 2e5 + 11;
const ll log_n = 40;
ll prev_[max_n][log_n];
ll dp[max_n][log_n];

void solve() {
    read(N);

    V<ll> A(N);
    forr(a, A) cin >> a;
    sort(all(A));
    A.erase(unique(all(A)), A.end());

    N = sz(A);
    rep(i, 0, N) {
        rep(s, 0, log_n) {
            dp[i][s] = 1;
            prev_[i][s] = -1;
        }
    }


    rep(i, 0, N) {
        rep(step, 0, log_n) {
            auto it = lower_bound(all(A), A[i] - (1 << step));
            if (it == A.end() || *it != A[i] - (1 << step) || i == it - A.begin()) continue;

            prev_[i][step] = it - A.begin();
            dp[i][step] += dp[it - A.begin()][step];
        }
    }

    ll max_el = 0, step = 0, idx = -1;
    for (ll i = N - 1; i >= 0; --i) {
        rep(s, 0, log_n) {
            if (dp[i][s] > max_el) {
                max_el = dp[i][s];
                step = s;
                idx = i;
            }
        }
    }

    cout << max_el << '\n';
    while (idx != -1) {
        cout << A[idx] << ' ';
        idx = prev_[idx][step];
    }
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
