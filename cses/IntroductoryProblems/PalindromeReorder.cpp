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
    int freq[28] = {0};

    for (const auto ch : s) ++freq[ch - 'A'];

    int idx = -1;
    for (int i = 0; i < 28; ++i) {
        if (freq[i] & 1) {
            if (idx != -1) {
                cout << "NO SOLUTION";
                return 0;
            }
            idx = i;
        }
    }

    for (int i = 0; i < 28; ++i) {
        for (int k = 0; k < freq[i] / 2; ++k) cout << (char)(i + 'A');
    }
    if (idx != -1) cout << (char)(idx + 'A');
    for (int i = 27; i >= 0; --i) {
        for (int k = 0; k < freq[i] / 2; ++k) cout << (char)(i + 'A');
    }
    cout << '\n';

    return 0;
}