//
// Created by aminjon on 9/23/22.
//
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int T; cin >> T;

    while (T--) {
        int N; cin >> N;
        string s; cin >> s;

        if (N > 2) sort(s.begin(), s.end());
        cout << s << '\n';
    }
    return 0;
}
