//
// Created by aminjon on 1/17/24.
//
#include <bits/stdc++.h>

// https://judge.yosupo.jp/submission/183891

// CDQ
template <typename T> struct PointAddRectangleSum {
  struct Event {
    T x, y, val;
    int sign, id;
  };
  std::vector<Event> events;
  std::vector<T> ans;

  auto modify(int x, int y, int val) {
    events.emplace_back(x, y, val, 0, -1);
  }
  auto query(int x1, int y1, int x2, int y2) { // bounds inclusive
    assert(x1 <= x2);
    assert(y1 <= y2);
    events.emplace_back(x2, y2, 0, +1, int(ans.size()));
    events.emplace_back(x1 - 1, y2, 0, -1, int(ans.size()));
    events.emplace_back(x2, y1 - 1, 0, -1, int(ans.size()));
    events.emplace_back(x1 - 1, y1 - 1, 0, +1, int(ans.size()));
    ans.emplace_back();
  }
  decltype(auto) work() {
    std::vector<T> xs, ys;
    for (const auto& ev : events) {
      xs.emplace_back(ev.x);
      ys.emplace_back(ev.y);
    }
    std::ranges::sort(xs);
    std::ranges::sort(ys);
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
    ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
    if (ys.size() > xs.size()) {
      for (auto& ev : events) {
        std::swap(ev.x, ev.y);
      }
      std::swap(xs, ys);
    }
    for (auto& ev : events) {
      ev.y = T(std::ranges::lower_bound(ys, ev.y) - ys.begin());
    }
    const auto n = int(ys.size());
    std::vector<T> bit(n + 1);
    auto upd = [&](T pos, T val) -> void {
      for (++pos; pos <= n; pos += pos & -pos) {
        bit[pos] += val;
      }
    };
    auto qry = [&](T pos) -> T {
      auto acc = T();
      for (++pos; pos > 0; pos -= pos & -pos) {
        acc += bit[pos];
      }
      return acc;
    };
    auto cdq = [&](auto& self, int l, int r) -> void {
      if (r - l <= 1) {
        return;
      }
      auto mid = l + (r - l) / 2;
      self(self, l, mid);
      self(self, mid, r);

      std::vector<Event> ord;
      int i = l, j = mid;
      for (; i < mid || j < r;) {
        if (j == r || i < mid && events[i].x <= events[j].x) {
          upd(events[i].y, events[i].val);
          ord.emplace_back(events[i++]);
        } else {
          if (events[j].id != -1) {
            ans[events[j].id] += qry(events[j].y) * events[j].sign;
          }
          ord.emplace_back(events[j++]);
        }
      }
      for (int k = l; k < mid; ++k) {
        if (events[k].val != 0) {
          upd(events[k].y, -events[k].val);
        }
      }
      for (int k = 0; k < ord.size(); ++k) {
        events[l + k] = ord[k];
      }
    };
    cdq(cdq, 0, events.size());
    return ans;
  }
};