//
// Created by aminjon on 8/27/22.
//
#include <iostream>
#include <vector>

/*
4
1 2 3 4
3
0 2
1 3
0 4
*/

auto solve() {
    size_t N;
    std::cin >> N;

    std::vector<int> f(N + 1, 0);

    decltype(auto) inc = [&f](size_t idx, int val) {
        for (++idx; idx < f.size(); idx += idx & -idx) f[idx] += val;
    };

    decltype(auto) sum = [&f](size_t idx) {
        int res = 0;
        for (++idx; idx > 0; idx -= idx & -idx) res += f[idx];

        return res;
    };

    for (size_t i = 0; i < N; ++i) {
        int val;
        std::cin >> val;
        inc(i, val);
    }

    size_t q;
    std::cin >> q;

    for (size_t i = 0; i < q; ++i) {
        size_t l, r;
        std::cin >> l >> r;
        std::cout << sum(r) - sum(l - 1) << std::endl;
    }
}

auto main() -> int32_t {
    solve();
}
