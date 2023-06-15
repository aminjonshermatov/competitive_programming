#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

constexpr auto  inf = numeric_limits<int>::max();
constexpr auto ninf = numeric_limits<int>::min();
constexpr int B = 3;

struct Block {
  int mn, mx;
  i64 sm;
  Block() : mn(inf), mx(ninf), sm(0) { }
  explicit Block(int x) : mn(x), mx(x), sm(x) { }
  friend string to_string(const Block &blk) {
    string s = "{mn="s;
    s.append(to_string(blk.mn));
    s.append(",mx="s);
    s.append(to_string(blk.mx));
    s.append(",sm="s);
    s.append(to_string(blk.sm));
    s.push_back('}');
    return s;
  }
};

void solve(int n, int q) {
  // ^ l, r, x -> a[i] = max(a[i], x), i := l..r
  // ? l, r    -> s / (l - r + 1), s += a[i], i := l..r

  vector<int> as(n, 0);

  vector<Block> blocks((n + B - 1) / B, Block(0));

  while (q--) {
    char cmd;
    int l, r;
    cin >> cmd >> l >> r;
    --l, --r;
    auto lb = l / B;
    auto rb = r / B;

    dbg(l+1, r+1, lb, rb);
    if (cmd == '^') {
      int x; cin >> x;

      if (lb == rb) {
        if (blocks[lb].mn == blocks[lb].mx) {
          for (int i = lb * B; i < min(n, (lb + 1) * B); ++i) {
            assert(as[i] <= blocks[lb].mn);
            as[i] = blocks[lb].mn;
          }
        }
        for (int i = l; i <= r; ++i) {
          as[i] = max(as[i], x);
        }
        Block nb;
        for (int i = lb * B; i < min(n, (lb + 1) * B); ++i) {
          nb.mn = min(nb.mn, as[i]);
          nb.mx = max(nb.mx, as[i]);
          nb.sm += as[i];
        }
        blocks[lb] = nb;
      } else {
        {
          if (blocks[lb].mn == blocks[lb].mx) {
            for (int i = lb * B; i < min(n, (lb + 1) * B); ++i) {
              as[i] = blocks[lb].mn;
            }
          }
          for (int i = l; i < min(n, (lb + 1) * B); ++i) {
            as[i] = max(as[i], x);
          }

          Block nb;
          for (int i = lb * B; i < min(n, (lb + 1) * B); ++i) {
            nb.mn = min(nb.mn, as[i]);
            nb.mx = max(nb.mx, as[i]);
            nb.sm += as[i];
          }
          blocks[lb] = nb;
        }

        for (int ib = lb + 1; ib < rb; ++ib) {
          if (blocks[ib].mn >= x) continue;
          if (blocks[ib].mx <= x) {
            blocks[ib].mn = blocks[ib].mx = x;
            blocks[ib].sm = i64(x) * B;
            continue;
          }
          if (blocks[ib].mn == blocks[ib].mx) {
            blocks[ib].mn = blocks[ib].mx = max(blocks[ib].mn, x);
            blocks[ib].sm = i64(x) * B;
            continue;
          }
          // neither
          for (int i = ib * B; i < (ib + 1) * B; ++i) {
            as[i] = max(as[i], x);
          }
          Block nb;
          for (int i = ib * B; i < (ib + 1) * B; ++i) {
            nb.mn = min(nb.mn, as[i]);
            nb.mx = max(nb.mx, as[i]);
            nb.sm += as[i];
          }
          blocks[ib] = nb;
        }
        {
          if (blocks[rb].mn == blocks[rb].mx) {
            for (int i = rb * B; i < min(n, (rb + 1) * B); ++i) {
              as[i] = blocks[rb].mn;
            }
          }
          for (int i = rb * B; i <= r; ++i) {
            as[i] = max(as[i], x);
          }
          Block nb;
          for (int i = rb * B; i < min(n, (rb + 1) * B); ++i) {
            nb.mn = min(nb.mn, as[i]);
            nb.mx = max(nb.mx, as[i]);
            nb.sm += as[i];
          }
          blocks[rb] = nb;
        }
      }
    } else if (cmd == '?') {
      i64 sm = 0;
      if (lb == rb) {
        if (blocks[lb].mn == blocks[lb].mx) {
          sm = i64(blocks[lb].mn) * (r - l + 1);
        } else {
          for (int i = l; i <= r; ++i) {
            sm += as[i];
          }
        }
      } else {
        if (blocks[lb].mn == blocks[lb].mx) {
          sm = i64(blocks[lb].mn) * (min(n, (lb + 1) * B) - l);
        } else {
          for (int i = l; i < min(n, (lb + 1) * B); ++i) {
            sm += as[i];
          }
        }

        for (int ib = lb + 1; ib < rb; ++ib) {
          sm += blocks[ib].sm;
        }

        if (blocks[rb].mn == blocks[rb].mx) {
          sm += i64(blocks[rb].mn) * (r - rb * B + 1);
        } else {
          for (int i = rb * B; i <= r; ++i) {
            sm += as[i];
          }
        }
      }
      i64 cnt = r - l + 1;
      auto g = gcd(sm, cnt);
      sm /= g;
      cnt /= g;
      if (cnt != 1 && sm != 0) {
        cout << sm << '/' << cnt << '\n';
      } else {
        cout << sm << '\n';
      }
    }
    dbg(as);
    dbg(blocks);
  }
}

bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, q;
  while (cin >> n >> q) {
    if (n == 0 && q == 0) break;
    solve(n, q);
  }

  return 0;
}
