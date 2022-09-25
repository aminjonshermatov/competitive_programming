//
// Created by aminjon on 9/25/22.
//
#include <iostream>
using namespace std;

using ll = long long;

int main() {
    int T; cin >> T;

    while (T--) {
        ll L, K; cin >> L >> K;

        cout << (L % K != 0) << '\n';
    }
    return 0;
}
