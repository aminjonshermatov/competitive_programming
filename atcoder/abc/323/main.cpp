#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = __int128;

struct TPoint {
  i64 x = 0, y = 0;
  friend istream& operator>>(istream &in, TPoint &pt) {
    int64_t x_, y_;
    in >> x_ >> y_;
    pt.x = x_;
    pt.y = y_;
    return in;
  }
  friend ostream& operator<<(ostream &out, const TPoint &pt) {
    return out << int64_t(pt.x) << ", " << int64_t(pt.y);
  }
};

void solve() {
  TPoint A{}, B{}, C{};
  cin >> A >> B >> C;

  const auto manhattanDistance = [&](const TPoint &a, const TPoint &b) -> i64 {
    return llabs(a.x - b.x) + llabs(a.y - b.y);
  };

  i64 ans = numeric_limits<i64>::max();
  ans *= 1e5;
  // 0 - x, 1 - y
  for (int first = 0; first < 2; ++first) {
    auto second = first ^ 1;

    auto cA = A, cB = B, cC = C;

    i64 tmp = 0;
    if (first == 0) {
      if (cC.x > cB.x) {
        auto nA = TPoint{cB.x - 1, cB.y};
        tmp += manhattanDistance(cA, nA);
        tmp += llabs(cC.x - cB.x);
        cB = TPoint{cC.x, cB.y};
        cA = TPoint{cB.x - 1, cB.y};
      } else {
        auto nA = TPoint{cB.x + 1, cB.y};
        tmp += manhattanDistance(cA, nA);
        tmp += llabs(cC.x - cB.x);
        cB = TPoint{cC.x, cB.y};
        cA = TPoint{cB.x + 1, cB.y};
      }
    } else {
      if (cC.y > cB.y) {
        auto nA = TPoint{cB.x, cB.y - 1};
        tmp += manhattanDistance(cA, nA);
        tmp += llabs(cC.y - cB.y);
        cB = TPoint{cB.x, cC.y};
        cA = TPoint{cB.x, cB.y - 1};
      } else {
        auto nA = TPoint{cB.x, cB.y + 1};
        tmp += manhattanDistance(cA, nA);
        tmp += llabs(cC.y - cB.y);
        cB = TPoint{cB.x, cC.y};
        cA = TPoint{cB.x, cB.y + 1};
      }
    }

    if (second == 0) {
      if (cC.x > cB.x) {
        auto nA = TPoint{cB.x - 1, cB.y};
        tmp += manhattanDistance(cA, nA);
        tmp += llabs(cC.x - cB.x);
        cB = TPoint{cC.x, cB.y};
        cA = TPoint{cB.x - 1, cB.y};
      } else {
        auto nA = TPoint{cB.x + 1, cB.y};
        tmp += manhattanDistance(cA, nA);
        tmp += llabs(cC.x - cB.x);
        cB = TPoint{cC.x, cB.y};
        cA = TPoint{cB.x + 1, cB.y};
      }
    } else {
      if (cC.y > cB.y) {
        auto nA = TPoint{cB.x, cB.y - 1};
        tmp += manhattanDistance(cA, nA);
        tmp += llabs(cC.y - cB.y);
        cB = TPoint{cB.x, cC.y};
        cA = TPoint{cB.x, cB.y - 1};
      } else {
        auto nA = TPoint{cB.x, cB.y + 1};
        tmp += manhattanDistance(cA, nA);
        tmp += llabs(cC.y - cB.y);
        cB = TPoint{cB.x, cC.y};
        cA = TPoint{cB.x, cB.y + 1};
      }
    }
    ans = min(ans, tmp);
  }
  cout << int64_t(ans) << '\n';
}

bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
