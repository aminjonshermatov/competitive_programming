#include <iostream>
using namespace std;

int main() {
    auto solve = []() -> void {
        int x; cin >> x;
        while (x > 0) {
            auto [q, r] = div(x, 10);
            if (r == 7) {
                cout << "YES\n";
                return;
            }
            x = q;
        }
        cout << "NO\n";
    };

    int t; cin >> t;
    while (t--) solve();
    return 0;
}
