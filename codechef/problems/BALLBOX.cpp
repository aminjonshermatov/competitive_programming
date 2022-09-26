//
// Created by aminjon on 9/26/22.
//
#include <iostream>
using namespace std;

using ll = long long;

int main() {
    ll T; cin >> T;

    while (T--) {
        ll N, K; cin >> N >> K;

        cout << (K * (K + 1) / 2 <= N ? "YES" : "NO") << '\n';
    }
    return 0;
}
