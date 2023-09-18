#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();

using pii = pair<int, int>;

inline int get_dir(char ch) {
    if (ch == 'N') return 0;
    if (ch == 'S') return 1;
    if (ch == 'W') return 2;
    if (ch == 'E') return 3;
    if (ch == 'U') return 4;
    if (ch == 'D') return 5;
    assert(false);
}

void solve() {
    array<string, 6> cmds{};
    for (int i = 0; i < 6; ++i) getline(cin, cmds[i]);

    array<map<int, int>, 6> memo{};
    int ans = 0;
    auto go = [&](auto f, int type, int k) -> int {
        if (k == 0) return 0;
        if (auto it = memo[type].find(k); it != memo[type].end()) return it->second;
        int cur = 1;
        for (auto to : cmds[type]) {
            auto temp = f(f, get_dir(to), k - 1);
            cur += temp;
        }
        ans = max(ans, cur);
        return memo[type][k] = cur;
    };

    char cmd;
    while (cin >> cmd) {
        assert(::isupper(cmd));
        int k; cin >> k;
        go(go, get_dir(cmd), k);
    }

    cout << ans << '\n';
}

//#define TIME

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef TIME
    auto start = chrono::steady_clock::now();
#endif

    int t = 1;
    //cin >> t;
    while (t--) solve();

#ifdef TIME
    auto finish = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";
#endif
}
