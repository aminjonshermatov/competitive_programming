//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "constants.h"

using i64 = int64_t;

struct Info {
  i64 height, width;
  Info(i64 height_, i64 width_) : height(height_), width(width_) { }
  Info() : Info(0, 0) { }

  bool operator<(const Info &other) const {
    return height < other.height;
  }

  friend std::ostream& operator<<(std::ostream& out, const Info &info) {
    return out << '{' << info.height << ' ' << info.width << '}';
  }
};

void solve(std::istream &in, std::ostream &out) {
  int n, q;
  in >> n >> q;

  std::vector<Info> infos;
  i64 prv_time = 0, cur_h = 0, tot_plus = 0, tot_minus = 0;
  for (int i = 0; i < n; ++i) {
    char op;
    i64 time, k;
    in >> op >> time >> k;

    infos.emplace_back(cur_h, time - prv_time);
    if (op == '+') {
      cur_h -= k;
      tot_plus += k;
    } else {
      cur_h += k;
      tot_minus += k;
    }
    prv_time = time;
  }
  std::sort(infos.rbegin(), infos.rend());
  while (!infos.empty() && infos.back().height < 0) {
    infos.pop_back();
  }
  std::reverse(infos.begin(), infos.end());
  n = int(infos.size());
  std::vector<i64> pf_area(n), pf_width(n);
  for (int i = 0; i < n; ++i) {
    pf_area[i] = (i > 0 ? pf_area[i - 1] : 0) + infos[i].width * infos[i].height;
    pf_width[i] = (i > 0 ? pf_width[i - 1] : 0) + infos[i].width;
  }

  while (q-- > 0) {
    i64 init;
    in >> init;

    if (tot_plus + init < tot_minus) {
      out << "INFINITY\n";
      continue;
    }

    assert(!infos.empty());
    int lo = -1, hi = n - 1;
    while (hi - lo > 1) {
      auto mid = lo + (hi - lo) / 2;
      (infos[mid].height >= init ? hi : lo) = mid;
    }
    out << std::max<i64>(0, pf_area.back() - (hi > 0 ? pf_area[lo] : 0) - init * (pf_width.back() - (hi > 0 ? pf_width[lo] : 0))) << '\n';
  }
}

int main() {
  auto in = std::ifstream(constants::DATA_IN);
  auto out = std::ofstream(constants::FAST_OUT);
  solve(in, out);

  return 0;
}
