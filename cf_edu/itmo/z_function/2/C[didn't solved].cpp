#include "bits/stdc++.h"

using namespace std;

void solve() {
    int N;
    cin >> N;
    vector<pair<int, int>> A1, A2;
    for (int i = 0; i < N; ++i) {
        int x;
        cin >> x;

        if (i == 0 && x != 0) { cout << "!\n"; return; }

        if (x == 0) A2.emplace_back(x, i);
        else A1.emplace_back(x, i);
    }

    set<char> free_ch;
    for (int i = 0; i < 26; ++i) free_ch.insert(i + 'a'), free_ch.insert(i + 'A');

    sort(A1.begin(), A1.end());
    string res(N, '#');

    for (auto &cont : {A1, A2}) {
        for (auto [z, i] : cont) {
            if (z == 0) {
                if (res[i] != '#') continue;
                if (free_ch.empty()) { cout << "!\n"; return; }
                auto it = free_ch.begin();
                res[i] = *it;
                free_ch.erase(it);
            } else {
                if (i + z > N) { cout << "!\n"; return; }
                for (int j = 0; j < z; ++j) {
                    if (res[j] == '#') {
                        if (res[i + j] == '#') {
                            if (free_ch.empty()) { cout << "!\n"; return; }
                            auto it = free_ch.begin();
                            res[j] = res[i + j] = *it;
                            free_ch.erase(it);
                        } else {
                            res[j] = res[i + j];
                        }
                    } else {
                        if (res[i + j] == '#') {
                            res[i + j] = res[j];
                        } else {
                            if (res[j] != res[i + j]) {
                                for (int ii = 0; ii < N; ++ii) cout << setw(2) << ii << ' ';
                                cout << '\n';
                                for (auto c : res) cout << setw(2) << c << ' ';
                                cout << '\n';
                                cout << j << ' ' << i + j << ' ' << i << ' ' << z << '\n';
                                cout << "--!\n";
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc;
    cin >> tc;

    while (tc--) solve();
}