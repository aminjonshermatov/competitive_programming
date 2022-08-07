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

const int SIZE = 2e5 + 1;
int res[SIZE] ={0};
array<int, 3> nums[SIZE];

void solve() {
    int n;
    cin >> n;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    int idx = 1;
    rep(i, 0, n) {
        cin >> nums[i][0] >> nums[i][1];
        nums[i][2] = (int)i;
    }

    sort(nums, nums + n, [](auto &lhs, auto &rhs) {
        if (lhs[0] == rhs[0]) return lhs[1] < rhs[1];
        return lhs[0] < rhs[0];
    });

    rep(i, 0, n) {
        int res_;
        if (pq.empty() || pq.top().F >= nums[i][0]) res_ = idx, pq.push(mk(nums[i][1], idx++));
        else {
            auto [_, ii] = pq.top(); pq.pop();
            pq.push(mk(nums[i][1], ii));
            res_ = ii;
        }
        res[nums[i][2]] = res_;
    }

    cout << idx - 1 << '\n';
    rep(i, 0, n) cout << res[i] << ' ';
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