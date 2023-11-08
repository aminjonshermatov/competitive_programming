#include <bits/stdc++.h>
#include "constants.h"

struct Segment {
  int l, r, id;
  bool operator<(const Segment &other) const {
    return l != other.l ? l < other.l : r < other.r;
  }
  friend std::ostream& operator<<(std::ostream &out, const Segment &seg) {
    return out << '{' << seg.l << ',' << seg.r << ',' << seg.id << '}';
  }
};

void solve(std::istream &in, std::ostream &out) {
  int n, m;
  in >> n >> m;
  std::vector<Segment> segments;
  for (int i = 0; i < m; ++i) {
    int l, r;
    in >> l >> r;

    auto cur = r - l + 1;
    std::vector<int> ids;
    int prv = 0;
    for (auto [ll, rr, id] : segments) {
      if (ll <= l && r <= rr) {
        prv += rr - ll + 1;
        ids.emplace_back(id);
      } else if (l <= ll && rr <= r) {
        prv += rr - ll + 1;
        ids.emplace_back(id);
      } else if (std::clamp(ll, l, r) == ll) {
        assert(r <= rr);
        prv += rr - ll + 1;
        ids.emplace_back(id);
      } else if (std::clamp(rr, l, r) == rr) {
        assert(ll <= l);
        prv += rr - ll + 1;
        ids.emplace_back(id);
      }
    }
    assert(std::set(ids.begin(), ids.end()).size() == ids.size());
    if (cur >= prv) {
      out << "1 " << ids.size() << ' ';
      std::sort(ids.begin(), ids.end());
      for (auto id : ids) {
        out << id + 1 << ' ';
      }
      out << '\n';
      std::vector<Segment> nseg;
      for (auto &seg : segments) {
        if (std::binary_search(ids.begin(), ids.end(), seg.id)) {
          continue;
        }
        nseg.emplace_back(seg);
      }
      segments.swap(nseg);
      segments.emplace_back(Segment{l, r, i});
    } else {
      out << "0 0\n";
    }
  }
}

int main() {
  std::ifstream in(constants::DATA_IN);
  std::ofstream out(constants::SLOW_OUT);

  solve(in, out);

  return 0;
}
