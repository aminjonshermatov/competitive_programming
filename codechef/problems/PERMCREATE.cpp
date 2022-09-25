//
// Created by aminjon on 9/25/22.
//
#include <iostream>
#include <vector>

using namespace std;
/*
2 4 1 3
3 1 4 2 5
4 1 5 2 6 3
4 1 5 2 6 3 7
*/
int main() {
    int T; cin >> T;

    while (T--) {
        int N; cin >> N;

        if (N > 4) {
            vector<int> A(N);
            int val = 1;
            for (int i = 1; i < N; i += 2) A[i] = val++;
            for (int i = 0; i < N; i += 2) A[i] = val++;

            for (const auto num : A) cout << num << ' ';
        } else if (N == 4) cout << "2 4 1 3";
        else cout << -1;
        cout << '\n';
    }
    return 0;
}
