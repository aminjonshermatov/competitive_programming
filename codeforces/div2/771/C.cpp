#include "bits/stdc++.h"

using namespace std;

template <typename T>
istream& operator>>(istream &in, vector<T> &arr) {
    for (auto &it : arr) in >> it;
    return in;
}

void solve() {
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc = 1;
    cin >> tc;

    while (tc--) solve();
}