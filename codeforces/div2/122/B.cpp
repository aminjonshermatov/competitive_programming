//#include "bits/stdc++.h"
//
//using namespace std;
//
//void solve() {
//    string s;
//    cin >> s;
//
//    int f = 0, z = 0, maxSub = 0;
//
//    for (const auto ch : s) {
//        if (ch == '0') ++z;
//        else ++f;
//
//        if (z != f) maxSub = max(maxSub, min(f, z));
//    }
//
//    cout << maxSub << '\n';
//}
//
//int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//    cout.tie(nullptr);
//
//    int tc;
//    cin >> tc;
//
//    while (tc--) {
//        solve();
//    }
//}