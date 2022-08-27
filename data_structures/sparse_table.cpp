//
// Created by aminjon on 8/27/22.
//

#include <iostream>
#include <vector>
#include <climits>

/*
4
1 2 3 4
3
0 2
1 3
0 4
*/

auto solve() {
    size_t n;
    std::cin >> n;

    const size_t lg_n = std::__lg(n);

    std::vector<std::vector<int>> st(lg_n + 1, std::vector<int>(n, 0));

    for (size_t i = 0; i < n; ++i) std::cin >> st[0][i];

    for (size_t level = 1; level <= lg_n; ++level) {
        for (size_t i = 0; i + (1 << level) <= n; ++i) {
            st[level][i] = std::max(st[level - 1][i], st[level - 1][i + (1 << (level - 1))]);
        }
    }

    for (size_t level = 0; level <= lg_n; ++level) {
        for (size_t i = 0; i + (1 << level) <= n; ++i) {
            std::cout << st[level][i] << ' ';
        }
        std::cout << std::endl;
    }

    decltype(auto) rmq = [&](size_t l, size_t r) {
        // auto t = std::__lg(r - l + 1);
        // return std::max(st[t][l], st[t][r + 1 - (1 << t)]);

        int res = INT_MIN;
        for (int level = static_cast<int>(lg_n); level >= 0; --level) {
            if (l + (1 << level) <= r + 1) {
                res = std::max(res, st[level][l]);
                l += (1 << level);
            }
        }

        return res;
    };

    size_t q;
    std::cin >> q;

    for (size_t i = 0; i < q; ++i) {
        size_t l, r;
        std::cin >> l >> r;

        std::cout << rmq(l, r) << std::endl;
    }
}

auto main() -> int32_t {
    solve();
}