#include "bits/stdc++.h"

using namespace std;

void solve() {
    string s, t;
    cin >> s >> t;

    int count = 0;
    for (int i = 0; i < s.size(); ++i) {
        bool isNotMatches = true;

        for (int j = i; j >= 0 and isNotMatches; --j) {
            // j...i

            for (int n = j; n <= i - static_cast<int>(t.size()) + 1; ++n) {
                bool localNotMatch = false;
                for (int m = 0; m < static_cast<int>(t.size()) and not localNotMatch; ++m) {
                    if (t[m] != s[n + m]) localNotMatch = true;
                }

                if (not localNotMatch) isNotMatches = false;
            }

            if (isNotMatches) ++count;
        }
    }

    cout << count << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc;
    cin >> tc;

    while (tc--) solve();
}