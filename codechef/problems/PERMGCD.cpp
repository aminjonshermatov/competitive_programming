//
// Created by aminjon on 9/26/22.
//
#include <iostream>
using namespace std;

using ll = long long;

int main() {
    ll T; cin >> T;

    while (T--) {
        ll N, X; cin >> N >> X;

        if (X - N < 0) cout << -1;
        else {
            ll A = X - N + 1;
            cout << A << ' ';
            for (int i = 1; i <= N; ++i) if (i != A) cout << i << ' ';
        }
        cout << '\n';
    }

    return 0;
}
