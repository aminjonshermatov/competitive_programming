#include "bits/stdc++.h"

using namespace std;

template <typename T>
istream& operator>>(istream &in, vector<T> &arr) {
    for (auto &it : arr) in >> it;
    return in;
}

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    cin >> nums;



    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc;
    cin >> tc;

    while (tc--) solve();
}