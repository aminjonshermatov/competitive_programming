//
// Created by aminjon on 9/28/22.
//
#include <iostream>
using namespace std;

int main() {
    int T; cin >> T;

    while (T--) {
        int ab, bc, ca;
        cin >> ab >> bc >> ca;

        cout << (ab == bc && ca >= ab || bc == ca && ab >= bc || ca == ab && bc >= ca ? "YES" : "NO") << '\n';
    }
    return 0;
}
