//
// Created by aminjon on 9/23/22.
//
#include <iostream>
using namespace std;

int main() {
    int T; cin >> T;

    while (T--) {
        int A, B; cin >> A >> B;

        cout << ((A & 1) + (B & 1) == 2 || A == 1 || B == 1 ? "NO" : "YES") << '\n';
    }
    return 0;
}
