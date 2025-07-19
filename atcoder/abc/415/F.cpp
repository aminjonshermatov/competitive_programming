#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

constexpr auto kBlockWidth = 750;

struct Info {
  char C = '#';
  int Len = 0;
};

struct BlockInfo {
  int Best = 0;
  Info Pre{};
  Info Suf{};
  int Len = 0;
};

void Solve() {
  int n, q;
  std::string s;
  Scan(n, q, s);

  const int nB = (n + kBlockWidth - 1) / kBlockWidth;
  std::vector<BlockInfo> blocks(nB);

  auto recalc = [&](const int ib) {
    const int l = ib * kBlockWidth;
    const int r = std::min(n, (ib + 1) * kBlockWidth) - 1;

    auto& b = blocks[ib];

    b = BlockInfo{};
    b.Len = r - l + 1;
    Info info{};
    for (int i = l; i <= r; ++i) {
      if (s[i] != info.C) {
        info.Len = 0;
      }
      info.C = s[i];
      b.Best = std::max(b.Best, ++info.Len);
    }
    b.Pre.C = s[l];
    for (int i = l; i <= r; ++i) {
      if (s[i] == s[l]) {
        ++b.Pre.Len;
      } else {
        break;
      }
    }
    b.Suf.C = s[r];
    for (int i = r; i >= l; --i) {
      if (s[i] == s[r]) {
        ++b.Suf.Len;
      } else {
        break;
      }
    }
  };

  for (int ib = 0; ib < nB; ++ib) {
    recalc(ib);
  }

  while (q-- > 0) {
    char cmd;
    Scan(cmd);
    if (cmd == '1') {
      int i;
      char x;
      Scan(i, x);

      s[--i] = x;
      recalc(i / kBlockWidth);
    } else {
      int l, r;
      Scan(l, r);
      --l, --r;

      auto ret = 0;
      const auto lb = l / kBlockWidth;
      const auto rb = r / kBlockWidth;
      if (lb == rb) {
        Info info{};
        for (int i = l; i <= r; ++i) {
          if (s[i] != info.C) {
            info.Len = 0;
          }
          info.C = s[i];
          ret = std::max(ret, ++info.Len);
        }
      } else {
        Info pre{};
        for (int i = l; i < (lb + 1) * kBlockWidth; ++i) {
          if (s[i] != pre.C) {
            pre.Len = 0;
          }
          pre.C = s[i];
          ret = std::max(ret, ++pre.Len);
        }
        // [lb+1, rb-1]
        Info suf{};
        for (int i = r; i >= rb * kBlockWidth; --i) {
          if (s[i] != suf.C) {
            suf.Len = 0;
          }
          suf.C = s[i];
          ret = std::max(ret, ++suf.Len);
        }
        for (int ib = lb + 1; ib < rb; ++ib) {
          const auto& b = blocks[ib];
          ret = std::max(ret, b.Best);
          if (pre.C == b.Pre.C) {
            ret = std::max(ret, pre.Len + b.Pre.Len);
            if (b.Pre.Len == b.Len) {
              pre.Len += b.Len;
            } else {
              pre = b.Suf;
            }
          } else {
            pre = b.Suf;
          }
        }
        if (pre.C == suf.C) {
          ret = std::max(ret, pre.Len + suf.Len);
        }
      }
      Println(ret);
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
