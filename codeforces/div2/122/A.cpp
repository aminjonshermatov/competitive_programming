//#include "bits/stdc++.h"
//
//using namespace std;
//
//void solve() {
//    int n;
//    cin >> n;
//
//    if (n % 7 == 0) {
//        cout << n << '\n';
//    } else {
//        auto cur{n / 10};
//        cur *= 10;
//        auto it{n % 10};
//        while (++it < 10) {
//            if ((cur + it) % 7 == 0) {
//                cout << cur + it << '\n';
//                return;
//            }
//        }
//
//        it = n % 10;
//        while (--it >= 0) {
//            if ((cur + it) % 7 == 0) {
//                cout << cur + it << '\n';
//                return;
//            }
//        }
//    }
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