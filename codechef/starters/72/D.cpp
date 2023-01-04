//
// Created by aminjon on 1/4/23.
//
#include <bits/stdc++.h>

using namespace std;

struct primes {
    int n;
    vector<int> lp, pr;

    explicit primes(int n_) : n(n_) { lp.assign(n + 1, 0); }

    auto find_primes() {
        for (int i = 2; i <= n; ++i) {
            if (lp[i] == 0) {
                lp[i] = i;
                pr.push_back(i);
            }
            for (int j = 0; i * pr[j] <= n; ++j) {
                lp[i * pr[j]] = pr[j];
                if (pr[j] == lp[i]) { break; }
            }
        }
    }
};

int main() {
    primes P(1e5);
    P.find_primes();

    int t;
    cin >> t;

    auto is_prime = [](auto x) -> bool {
        if (x < 2) return false;
        if (x == 2) return true;
        if (x % 2 == 0) return false;
        for (int i = 3; i * 1ll * i <= x; i += 2) if (x % i == 0) return false;
        return true;
    };

    auto test_case = [&]() {
        int n;
        cin >> n;
        if (n < 6 || is_prime(n)) {
            cout << -1 << '\n';
            return;
        }

        if (n & 1) {
            for (auto x : P.pr) {
                auto [q, r] = div(n, x);
                if (r == 0 && q != x) {
                    cout << 1 << ' ' << x << ' ' << q << '\n';
                    return;
                }
            }
            cout << -1 << '\n';
        } else {
            cout << "1 2 " << n / 2 << '\n';
        }
    };

    while (t--) test_case();
    return 0;
}
