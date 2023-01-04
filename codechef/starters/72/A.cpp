//
// Created by aminjon on 1/4/23.
//
#include <iostream>
using namespace std;

int main() {
    int t; cin >> t;
    while(t--) {
        int a, b, c; cin >> a >> b>> c;
        cout << (a+b == c ? "YES\n" : "NO\n");
    }
    return 0;
}
