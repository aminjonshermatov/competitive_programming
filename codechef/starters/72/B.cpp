//
// Created by aminjon on 1/4/23.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >>t;
    while (t--) {
        array<int, 3> A;
        for (int i = 0; i < 3; ++i) cin >> A[i];
        for (int k = 2; k < 100; ++k) {
            if (all_of(A.begin(), A.end(), [k](auto x) { return x % k != 0; })) {
                cout << k << '\n';
                break;
            }
        }
    }
    return 0;
}
