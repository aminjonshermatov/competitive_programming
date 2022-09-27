//
// Created by aminjon on 9/27/22.
//
#include <iostream>
using namespace std;

using ll = long long;

int main() {
    ll N; cin >> N;

    ll bad = 0;
    for (ll i = 0, j = 0, k = 1; k != N * N + 1; ++k) {
        ll a; cin >> a;
        if (a == 1 && (i % 2 == 0 || j % 2 == 0)) ++bad;
        if (++j == N) j = 0, ++i;
    }

    if (bad > 0) cout << "Improper Placement" << '\n' << bad;
    else cout << "Proper Placement";
    cout << '\n';

    return 0;
}
