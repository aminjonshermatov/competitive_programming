#include "bits/stdc++.h"

using namespace std;

template <typename T>
istream& operator>>(istream &in, vector<T> &arr) {
    for (auto &it : arr) in >> it;
    return in;
}

namespace std {
    template <> struct hash<pair<int64_t, int64_t>> {
        inline size_t operator()(const pair<int64_t, int64_t> &v) const {
            hash<int64_t> int_hasher;
            return int_hasher(v.first) ^ int_hasher(v.second);
        }
    };
}

void solve() {
    int64_t n, x, y;
    cin >> n >> x >> y;
    vector<int> nums(n);
    for (auto &num : nums) cin >> num;

    int64_t sum = accumulate(nums.begin(), nums.end(), 0);

    if (x + sum == y) cout << "Alice";
    else if (x + sum + 3 == y) cout << "Bob";
    else {
        for (int64_t i = n - 1; i >= 0; --i) {
            if (sum >= nums[i]) sum -= nums[i];
            sum ^= nums[i];

            if (x + sum == y) {
                cout << "Alice" << '\n';
                return;
            }

            if (x + 3 + sum == y) {
                cout << "Bob" << '\n';
                return;
            }
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc = 1;
    cin >> tc;

    while (tc--) solve();
}