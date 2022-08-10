#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
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
#define read(T, k) T k; cin >> k

#define IOS ios_base::sync_with_stdio(false); \
            cin.tie(nullptr);                 \
            cout.tie(nullptr);

template<typename T = ll>
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

mt19937 rnd(143);

const ll inf = 1e15;
const ll M = 1e9 + 7;
[[maybe_unused]] const ld pi = atan2(0, -1);
const ld eps = 1e-6;

// ========================================= PROBLEM =========================================

void solve() {
    int N, T; cin >> N >> T;

    vector<pair<int64_t, ll>> A(N);
    rep (i, 0, N) cin >> A[i].F, A[i].S = i;
    sort(all(A));

    array<ll, 4> ans;
    bool ok = false;
    for (ll i = 1; i < N && !ok; ++i) {
        for (ll j = 0; j < i && !ok; ++j) {
            for (ll k = i + 1, l = N - 1; k < l;) {
                auto t = A[i].F + A[j].F + A[k].F + A[l].F;
                if (t < T) ++k;
                else if (t > T) --l;
                else {
                    ok = true;
                    ans = {A[i].S + 1, A[j].S + 1, A[k].S + 1, A[l].S + 1};
                    break;
                }
            }
        }
    }

    if (ok)
        rep (i, 0, 4) cout << ans[i] << " \n"[i == 3];
    else
        cout << "IMPOSSIBLE";
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