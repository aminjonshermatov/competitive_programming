#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;

inline constexpr array<int, 3> dX{-1, 0, 1};

int main() {
    auto test_case = []() {
        i64 n, k, s; cin >> n >> k >> s;
        array<map<i64, vector<int>>, 100> memo;

        vector<int> B(n, -2);
        auto rec = [&](auto self, uint cur_i, i64 kK, i64 sS) -> bool {
            if (cur_i >= n) {
                if (s == sS) {
                    fill(B.begin() + cur_i, B.end(), 0);
                    return true;
                }
                return false;
            }

            if (auto it = memo[cur_i].find(sS); it != memo[cur_i].end()) {
                for (int i = cur_i; i < n; ++i) B[i] = it->second[i];
                return true;
            }

            for (auto xx : dX) {
                if (self(self, cur_i + 1, kK*k, sS + xx*kK)) {
                    B[cur_i] = xx;
                    memo[cur_i].emplace(sS+xx*kK, B);
                    return true;
                }
            }

            return false;
        };

        if (rec(rec, 0, 1, 0)) {
            for (auto x : B) cout << x << ' ';
            cout << '\n';
        } else cout << -2 << '\n';
    };

    int t; cin >> t;
    while (t--) test_case();

    return 0;
}
