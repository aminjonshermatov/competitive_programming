//
// Created by aminjon on 1/1/23.
//
#include <bits/stdc++.h>

using namespace std;

struct primes {
    ll n;
    vector<ll> lp, pr;

    explicit primes(ll n_) : n(n_) { lp.assign(n + 1, 0); }

    auto find_primes() {
        for (ll i = 2; i <= n; ++i) {
            if (lp[i] == 0) {
                lp[i] = i;
                pr.push_back(i);
            }
            for (ll j = 0; i * pr[j] <= n; ++j) {
                lp[i * pr[j]] = pr[j];
                if (pr[j] == lp[i]) { break; }
            }
        }
    }
};