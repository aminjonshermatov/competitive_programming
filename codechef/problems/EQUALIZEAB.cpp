//
// Created by aminjon on 9/25/22.
//
#include <iostream>
using namespace std;

/*
a=a+ix-jx
b=b-ix+jx

a+ix-jx=b-ix+jx
a+2ix=b+2jx
a-b=2x(j-i)
*/

using ll = long long;

int main() {
    int T; cin >> T;

    while (T--) {
        ll A, B, X;
        cin >> A >> B >> X;

        cout << ((A - B) % (2 * X) == 0 ? "YES" : "NO") << '\n';
    }
    return 0;
}
