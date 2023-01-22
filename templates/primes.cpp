//
// Created by aminjon on 1/1/23.
//
#include <bits/stdc++.h>

using namespace std;

template<typename T> struct Primes {
    T n;
    vector<T> lp, pr;

    using iterator          = vector<T>::iterator;
    using const_iterator    = vector<T>::const_iterator;

    explicit Primes(T n_) : n(n_) { lp.assign(n + 1, T(0)); find_primes(); }

    auto find_primes() -> void {
        for (T i = 2; i <= n; ++i) {
            if (lp[i] == 0) {
                lp[i] = i;
                pr.push_back(i);
            }
            for (T j = 0; i * pr[j] <= n; ++j) {
                lp[i * pr[j]] = pr[j];
                if (pr[j] == lp[i]) break;
            }
        }
    }

    iterator begin() { return pr.begin(); }
    [[nodiscard]] const_iterator begin() const { return pr.begin(); }
    iterator end() { return pr.end(); }
    [[nodiscard]] const_iterator end() const { return pr.end(); }
};