#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<vector<bool>> board(8, vector<bool>(8));
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            char ch;
            cin >> ch;
            board[i][j] = ch == '.';
        }
    }

    vector<bool> cols(8, true);
    vector<vector<bool>> diagonal(2, vector<bool>(15, true));

    int res = 0;
    function<void(int, int)> b = [&](int row, int prev) {
        if (row >= 8) {
            ++res;
            return;
        }

        for (int j = 0; j < 8; ++j) {
            if ((j >= prev - 1 && j <= prev + 1) || !cols[j] || !diagonal[0][7 + row - j] || !diagonal[1][row + j] || !board[row][j]) continue;
            cols[j] = false;
            diagonal[0][7 + row - j] = false;
            diagonal[1][row + j] = false;
            b(row + 1, j);
            diagonal[0][7 + row - j] = true;
            diagonal[1][row + j] = true;
            cols[j] = true;
        }
    };

    b(0, -3);
    cout << res << '\n';

    return 0;
}