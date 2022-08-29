#include "bits/stdc++.h"

using namespace std;

int main() {
    int N; cin >> N;

    vector<pair<int, int>> res;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            char ch; cin >> ch;
            if (ch == '1' && j >= i) res.emplace_back(i + 1, j + 1);
        }
    }

    cout << res.size() << '\n';
    for (auto it : res) cout << it.first << ' ' << it.second << '\n';
}