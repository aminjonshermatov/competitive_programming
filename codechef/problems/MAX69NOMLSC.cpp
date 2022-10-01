//
// Created by aminjon on 10/1/22.
//
#include <iostream>
using namespace std;

using ll = long long;

int main() {
    int T; cin >> T;

    while (T--) {
        string s; cin >> s;

        const int N(s.size());
        for (int i = 0; i < N; ++i) {
            if (s[i] == '6') {
                s[i] = '9';
                break;
            }
        }

        cout << s << '\n';
    }
    return 0;
}
