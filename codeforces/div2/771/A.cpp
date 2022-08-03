#include "bits/stdc++.h"

using namespace std;

template <typename T>
istream& operator>>(istream &in, vector<T> &arr) {
    for (auto &it : arr) in >> it;
    return in;
}

template <typename T>
ostream& operator<<(ostream &out, vector<T> &arr) {
    cout << '[';
    for (auto &it : arr) out << it << ' ';
    return out << ']';
}

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (auto &num : nums) cin >> num;

    auto res{nums};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            // j..i
            if (res[j] > res[i]) {
                reverse(nums.begin() + j, nums.begin() + i + 1);
                res = min(res, nums);
                reverse(nums.begin() + j, nums.begin() + i + 1);
            }
        }
    }

    for (const auto num : res) cout << num << ' ';
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