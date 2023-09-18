#include <bits/stdc++.h>

using namespace std;

using i64 =  ::int64_t;
using u64 = ::uint64_t;

inline constexpr auto  inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();

void solve() {
    const int n = 3;
    array<i64, n> T{};
    for (int i = 0; i < n; ++i) {
        int h, m, s;
        char _;
        cin >> h >> _ >> m >> _ >> s;
        T[i] = i64(1) * h * 60 * 60 + i64(1) * m * 60 + s;
    }

    auto print = [&](i64 time) -> void {
        time = time % (24 * 3600);
        auto hour = time / 3600;
        time %= 3600;
        auto minutes = time / 60 ;
        time %= 60;
        auto seconds = time;
        cout << setw(2) << setfill('0') << hour << ':' <<
                setw(2) << setfill('0') << minutes << ':' <<
                setw(2) << setfill('0') << seconds << '\n';
    };

    const i64 MOD = 24 * 60 * 60;
    auto diff = (T[n - 1] - T[0] + MOD + 1) % MOD / 2;
    print(T[1] + diff);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}