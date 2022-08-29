#include "bits/stdc++.h"

using namespace std;

int main() {
    int N; cin >> N;
    vector<string> M(N);
    for (auto &l : M) cin >> l;

    for (int i = 0; i < N; ++i) {
        int cnt = 0;
        for (auto ch : M[i]) cnt += ch - '0';

        cout << cnt << ' ';
        for (int j = 0; j < N; ++j) if (M[i][j] == '1') cout << j + 1 << ' ';
        cout << '\n';
    }
}