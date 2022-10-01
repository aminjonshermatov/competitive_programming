#include "bits/stdc++.h"

using namespace std;

using ll = long long;

int main() {
    ll N; cin >> N;

    string s = "1";
    for (int i = 0; i < N; ++i) {
        ll rem = 0;
        for (auto &ch : s) {
            ll num = 2 * (ll)(ch - '0') + rem;
            ch = char(num % 10) + '0';
            rem = num / 10;
        }
        if (rem != 0) s.push_back(char(rem) + '0');
    }

    reverse(s.begin(), s.end());
    cout << s << '\n';

    return 0;
}