#include <bits/stdc++.h>

using namespace std;

int main() {
  int n; cin >> n;
  static int ans = 0;
  struct __foo {
    void operator()(int _1, int _2) {
      ++ans;
      if (_2 - _1 < 3) return;
      auto _3 = (_2 - _1) / 3;
      auto _l = _1 + _3;
      auto _r = _2 - _3;
      if (rand() & 1) {
        __foo()(_l, _2);
      } else {
        __foo()(_1, _r);
      }
    }
  };
  __foo()(false + 1, n - false);
  cout << ans << '\n';
}
