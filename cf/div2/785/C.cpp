#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

static constexpr size_t MOD = 1e9 + 7;
static constexpr size_t MAX = 4e4 + 1;
static bool pal[MAX] = {false};

bool isPal(int n) {
    int cur[5] {0};
    int i = 4;
    while (n > 0) {
        cur[i--] = n % 10;
        n /= 10;
    }

    int s = 0;
    while (s < 5 && cur[s] == 0) ++s;
    for (int j = 4; s < j; ++s, --j) {
        if (cur[s] != cur[j]) return false;
    }
    return true;
}

void precompute() {
    for (int i = 1; i < 10; ++i) pal[i] = true;
    for (int i = 11; i < MAX; ++i) pal[i] = isPal(i);
}

void solve() {
    int n;
    cin >> n;

    vector<int> dp(n + 1, -1);
    vector<bool> visited(n + 1, false);

    const function<int(const int)> dfs = [&](const int target) -> int {
        cout << target << '\n';
        if (target < 0) return 0;
        if (target == 0) return 1;
        if (dp[target] != -1) return dp[target];

        //visited[target] = true;
        int sum = 0;
        for (int i = target; i > 0; --i) {
            if (pal[i] && !visited[target - i]) {
                cout << target << "->" << target - i << '\n';
                sum += dfs(target - i);
            }
        }

        return dp[target] = sum;
    };


    dfs(n);
    for (int i = 0; i <= n; ++i) cout << dp[i] << ' ';
    cout << '\n';

    cout << dp[n] << '\n';
}

int main() {
    // auto start = chrono::steady_clock::now();

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    precompute();
    int T = 1;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        // cout << "Case #" << tc << ": ";
        solve();
        // cout << '\n';
    }

    // auto finish = chrono::steady_clock::now();
    // auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    // cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";

    return 0;
}