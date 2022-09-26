//
// Created by aminjon on 9/26/22.
//
#include <iostream>
#include <map>
#include <vector>

using namespace std;

using ll = long long;

/*
lcm(a, b) = a * b / gcd(a, b);

gcd(a, b) = a * b / gcd(a, b);

gcd^2(a, b) = a * b;
*/

int main() {
    int T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        map<ll, ll> fr;
        for (ll i = 0; i < N; ++i) {
            ll temp; cin >> temp;
            ++fr[temp];
        }

        ll ans = 0;
        for (auto [n, c] : fr) ans += c * (c - 1) >> 1;

        cout << ans << '\n';
    }

    return 0;
}

