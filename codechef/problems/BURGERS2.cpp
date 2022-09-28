//
// Created by aminjon on 9/28/22.
//
#include <iostream>
using namespace std;

using ll = long long;

/*
n1*X+n2*Y<=R
n1+n2=N
n2 - max

n1 = N - n2

(N - n2)*X+n2*Y<=R
N*X-n2*X+n2*Y<=R
n2*(Y-X)<=R - N*X
n2<=(R-N*X)/(Y-X)
*/

int main() {
    ll T; cin >> T;

    while (T--) {
        ll X, Y, N, R;
        cin >> X >> Y >> N >> R;

        if (X * N > R) {
            cout << -1 << '\n';
            continue;
        }

        ll n2 = min(N, (R - N * X) / (Y - X));
        cout << N - n2 << ' ' << n2 << '\n';
    }
    return 0;
}
