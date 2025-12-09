#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

struct Point final {
  int64_t X = 0, Y = 0;

  friend std::ostream& operator<<(std::ostream& out, const Point& pt) {
    return out << std::format("{{{},{}}}", pt.X, pt.Y);
  }
};

constexpr int kN = 496;
std::array<Point, kN> pts;

int64_t ret = 0, done = 0;
std::mutex mtx;

void Work(const int i) {
  std::map<std::pair<int, int>, bool> cache;
  auto isInside = [&cache](const auto x, const auto y) {
    if (cache.size() > 5E7) {
      cache.clear();
    }
    const auto key = std::pair(x, y);
    if (auto it = cache.find(key); it != cache.end()) {
      return it->second;
    }
    auto inside = false;
    auto onBorder = false;
    for (int me = 0; me < kN; ++me) {
      const auto [xa, ya] = pts[(me + kN - 1) % kN];
      const auto [xb, yb] = pts[me];

      if (xa == xb && xb == x) {
        if (std::clamp(y, std::min(ya, yb), std::max(ya, yb)) == y) {
          onBorder = true;
          break;
        }
      } else if (ya == yb && yb == y) {
        if (std::clamp(x, std::min(xa, xb), std::max(xa, xb)) == x) {
          onBorder = true;
          break;
        }
      }
      if ((ya > y) != (yb > y)) {
        assert(xa == xb);
        if (x < xa) {
          inside ^= true;
        }
      }
    }
    return cache[key] = onBorder || inside;
  };
  auto canReach = [&](int i, int j) -> bool {
    if (pts[i].X == pts[j].X || pts[i].Y == pts[j].Y) {
      return true;
    }
    for (auto x = std::min(pts[i].X, pts[j].X); x <= std::max(pts[i].X, pts[j].X); ++x) {
      if (!isInside(x, pts[i].Y) || !isInside(x, pts[j].Y)) {
        return false;
      }
    }
    for (auto y = std::min(pts[i].Y, pts[j].Y); y <= std::max(pts[i].Y, pts[j].Y); ++y) {
      if (!isInside(pts[i].X, y) || !isInside(pts[j].X, y)) {
        return false;
      }
    }
    return true;
  };
  auto loc = int64_t{0};
  for (int j = i + 1; j < kN; ++j) {
    if (canReach(i, j)) {
      loc = std::max(loc, (std::abs(pts[i].X - pts[j].X) + 1) * (std::abs(pts[i].Y - pts[j].Y) + 1));
    }
  }
  {
    std::lock_guard lock(mtx);
    ret = std::max(ret, loc);
    ++done;
    std::cerr << "done= " << done << " cur=" << i << " ret=" << ret << std::endl;
  }
}

void Solve() {
  for (char _; auto& [x, y] : pts) {
    Scan(x, _, y);
  }

  for (int i = 0; i < kN; ++i) {
    assert(pts[i].X == pts[(i + 1) % kN].X || pts[i].Y == pts[(i + 1) % kN].Y);
  }

  std::array<std::jthread, kN> threads;
  for (int i = 0; i < kN; ++i) {
    threads[i] = std::jthread(Work, i);
  }
  for (auto& tr : threads) {
    tr.join();
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
