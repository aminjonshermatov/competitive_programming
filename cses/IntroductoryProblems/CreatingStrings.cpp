#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s; cin >> s;
    sort(s.begin(), s.end());
    set<string> poss;

    function<void(int)> b_ = [&](int pos) {
        if (pos == s.size()) {
            poss.insert(s);
            return;
        }

        for (int i = pos; i < s.size(); ++i) {
            if (i != pos && s[i] == s[pos]) continue;
            swap(s[i], s[pos]);
            b_(pos + 1);
            swap(s[i], s[pos]);
        }
    };

    b_(0);

    cout << poss.size() << '\n';
    for (const auto &s_ : poss) cout << s_ << '\n';

    return 0;
}