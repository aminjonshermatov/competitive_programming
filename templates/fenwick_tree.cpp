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

using namespace std;
using ll = long long;

struct ftree {
    vector<ll> A, B;
    ll N;

    explicit ftree(ll N_) : N{N_} {
        A.assign(N + 1, 0);
        B.assign(N + 1, 0);
    }

    void add(vector<ll> &C, ll idx, ll v) {
        while (idx <= N) {
            C[idx] += v;
            idx += idx & -idx;
        }
    }

    // [l, r]
    void range_add(ll l, ll r, ll v) {
        add(A, l, v);
        add(A, r + 1, -v);
        add(B, l, v * (l - 1));
        add(B, r + 1, -v * r);
    }

    ll sum(vector<ll> &C, ll idx) {
        ll ans = 0;
        while (idx > 0) {
            ans += C[idx];
            idx -= idx & -idx;
        }
        return ans;
    }

    ll prefix_sum(ll idx) {
        return sum(A, idx) * idx - sum(B, idx);
    }

    ll range_sum(ll l, ll r) {
        return prefix_sum(r) - prefix_sum(l - 1);
    }
};