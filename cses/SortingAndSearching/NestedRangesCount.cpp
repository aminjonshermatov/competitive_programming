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

#define f first
#define s second
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


const int MAX_N = 2e5 + 1;
const int SIZE = MAX_N << 1;

array<int, 3> A[MAX_N];
int bit[SIZE] = {0};
int res[2][MAX_N] = {0};
set<int> uniq;
map<int, int> num2idx;

int sum(int idx) {
    int res_ = 0;
    for (int i = idx; i > 0; i -= i & -i) res_ += bit[i];

    return res_;
}

void update(int idx, int val) {
    for (int i = idx; i < SIZE; i += i & -i) bit[i] += val;
}

void solve() {
    int n; cin >> n;

    rep(i, 0, n) {
        int x, y; cin >> x >> y;

        A[i] = {x, y, (int)i};
        uniq.insert(x);
        uniq.insert(y);
    }

    int idx = 1;
    for (auto num : uniq) num2idx[num] = idx++;

    sort(A, A + n, [](const auto &lhs, const auto &rhs) {
        if (lhs[0] == rhs[0]) return lhs[1] > rhs[1];
        return lhs[0] < rhs[0];
    });

    for (int i = n - 1; i >= 0; --i) {
        auto _idx = num2idx[A[i][1]];
        res[0][A[i][2]] = sum(_idx);
        update(_idx, 1);
    }

    fill(bit, bit + SIZE, 0);
    rep(i, 0, n) {
        auto _idx = num2idx[A[i][1]];
        res[1][A[i][2]] = (int)i - sum(_idx - 1);
        update(_idx, 1);
    }

    rep(i, 0, 2) {
        rep(j, 0, n) cout << res[i][j] << " \n"[j == n - 1];
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