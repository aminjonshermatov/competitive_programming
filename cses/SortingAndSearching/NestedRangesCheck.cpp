#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

typedef long long ll;
typedef unsigned long long ull;
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


// ========================================= PROBLEM =========================================

static const int MAX_N = 2e5 + 1;
static const int SIZE = MAX_N << 1;
int ans[2][MAX_N], bit[SIZE];

static array<int, 3u> A[MAX_N];
static set<int> uniq;
static map<int, int> num2idx;

int sum(int idx) {
    int res_ = 0;
    for (int i = idx; i > 0; i -= i & -i) res_ += bit[i];
    return res_;
}

void update(int idx, int val) {
    for (int i = idx; i < SIZE; i += i & -i) bit[i] += val;
}

void solve() {
    int N;
    cin >> N;
    fill(bit, bit + SIZE, 0);

    for (int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;

        A[i] = {x, y, i};
        uniq.insert(x);
        uniq.insert(y);
    }

    int idx = 1;
    for (auto num: uniq) num2idx[num] = idx++;

    std::sort(A, A + N, [](auto &lhs, auto &rhs) {
        if (lhs[0] == rhs[0]) return lhs[1] > rhs[1];
        return lhs[0] < rhs[0];
    });

    for (int i = N - 1; i >= 0; --i) {
        int _idx = num2idx[A[i][1]];
        ans[0][A[i][2]] = sum(_idx);
        update(_idx, 1);
    }

    fill(bit, bit + SIZE, 0);
    for (int i = 0; i < N; ++i) {
        int _idx = num2idx[A[i][1]];
        ans[1][A[i][2]] = i - sum(_idx - 1);
        update(_idx, 1);
    }

    rep(i, 0, 2)
        rep(j, 0, N) cout << (ans[i][j] ? 1 : 0) << " \n"[j == N - 1];
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