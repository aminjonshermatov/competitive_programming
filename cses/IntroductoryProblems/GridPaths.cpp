#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define ll int64_t
#define ull uint64_t

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s; cin >> s;
    ull res = 0;
    vector<vector<bool>> visited(7, vector<bool>(7, false));

    function<void(int, int, int)> dfs = [&](int y, int x, int i) {
        if (y == 6 && x == 0) {
            if (i == 48) ++res;
            return;
        }

        visited[y][x] = true;
        if ((s[i] == '?' || s[i] == 'U') && y - 1 >= 0 && !visited[y - 1][x]) {
            dfs(y - 1, x, i + 1);
        }
        if ((s[i] == '?' || s[i] == 'D') && y + 1 < 7 && !visited[y + 1][x]) {
            dfs(y + 1, x, i + 1);
        }
        if ((s[i] == '?' || s[i] == 'L') && x - 1 >= 0 && !visited[y][x - 1]) {
            dfs(y, x - 1, i + 1);
        }
        if ((s[i] == '?' || s[i] == 'R') && x + 1 < 7 && !visited[y][x + 1]) {
            dfs(y, x + 1, i + 1);
        }
        visited[y][x] = false;
    };

    dfs(0, 0, 0);

    cout << res << '\n';
    return 0;
}