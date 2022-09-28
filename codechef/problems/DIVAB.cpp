//
// Created by aminjon on 9/28/22.
//
#include "bits/stdc++.h"

using namespace std;

using ll = long long;

int main() {
    ll T; cin >> T;

    while (T--) {
        ll A, B, N;
        cin >> A >> B >> N;

        if (A % B == 0) {
            cout << "-1\n";
            continue;
        }

        auto k = N;
        if (N % A != 0) k  += A - (N % A);

        while (k % B == 0) k += A;

        cout << k << '\n';
    }
    return 0;
}
