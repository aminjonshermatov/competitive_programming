//
// Created by aminjon on 1/4/23.
//
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int t; cin >>t;
    while (t--) {
        int n, m; cin >> n >> m;
        cout << __gcd(n, m) << '\n';
    }
    return 0;
}
