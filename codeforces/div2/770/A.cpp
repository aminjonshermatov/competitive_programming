#include "bits/stdc++.h"

using namespace std;

template <typename T>
istream& operator>>(istream &in, vector<T> &arr) {
    for (auto &it : arr) in >> it;
    return in;
}

inline bool isPalindrome(const string &s) {
    const int n = static_cast<int>(s.size());

    for (int i = 0; i < (n >> 1); ++i) {
        if (s[i] != s[n - i - 1]) return false;
    }

    return true;
}

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    if (n == 1 or k == 0) cout << 1;
    else cout << static_cast<int>(not isPalindrome(s)) + 1;
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc = 1;
    cin >> tc;

    while (tc--) solve();
}