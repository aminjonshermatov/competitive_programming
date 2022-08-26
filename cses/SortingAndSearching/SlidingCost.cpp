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
#define read(T, k) T k; cin >> k

#define IOS ios_base::sync_with_stdio(false); \
            cin.tie(nullptr);                 \
            cout.tie(nullptr);

template<typename T = ll>
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

[[maybe_unused]] mt19937 rnd(143);

const ll inf = 1e15;
const ll M = 1e9 + 7;
[[maybe_unused]] const ld pi = atan2(0, -1);
const ld eps = 1e-6;

// ========================================= PROBLEM =========================================

auto upd(vector<ll>& arr, ll idx, ll val) {
    for (++idx; idx < arr.size(); idx += idx & -idx) arr[idx] += val;
}

auto sum(const vector<ll>& arr, ll idx, ll res = 0) {
    for (++idx; idx > 0; idx -= idx & -idx) res += arr[idx]; return res;
}

void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N), bit_v(N + 1, 0), bit_f(N + 1, 0);
    vector<pair<ll, ll>> num2Idx(N);
    rep (i, 0, N) {
        cin >> A[i];
        num2Idx[i].F = A[i];
        num2Idx[i].S = i;
    }

    sort(all(num2Idx));
    rep (i, 0, N) A[num2Idx[i].S] = i;

    rep (i, 0, N) {
        upd(bit_f, A[i], 1);
        upd(bit_v, A[i], num2Idx[A[i]].F);

        if (i + 1 >= K) {
            ll lo = 0, hi = (ll)bit_f.size() - 2;
            while (lo < hi) {
                auto mid = lo + (hi - lo) / 2;

                if (sum(bit_f, mid) < (K + 1) / 2) lo = mid + 1;
                else hi = mid;
            }

            cout << sum(bit_v, N - 1) - 2 * sum(bit_v, lo) + ((K & 1) ? num2Idx[lo].F : 0) << ' ';

            upd(bit_f, A[i + 1 - K], -1);
            upd(bit_v, A[i + 1 - K], -num2Idx[A[i + 1 - K]].F);
        }
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