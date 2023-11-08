//
// Created by aminjon on 4/13/23.
//
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

bool check() {
  std::ifstream data(constants::DATA_IN);
  std::ifstream slow(constants::SLOW_OUT);
  std::ifstream fast(constants::FAST_OUT);

  int n, m;
  data >> n >> m;
  std::vector<Segment> segs(m);
  for (int i = 0; auto &[l, r, id] : segs) {
    data >> l >> r;
    id = i++;
  }

  for (int i = 0; i < m; ++i) {
    bool ss;
    slow >> ss;
    int s_len;
    slow >> s_len;
    std::vector<int> s_ids(s_len);
    for (auto &id : s_ids) {
      slow >> id;
    }

    bool ff;
    fast >> ff;
    int f_len;
    fast >> f_len;
    std::vector<int> f_ids(f_len);
    for (auto &id : f_ids) {
      fast >> id;
    }

    if (ss != ff || s_ids != f_ids) {
      std::cerr << n << ' ' << m << '\n';
      for (auto &seg : segs) {
        std::cerr << seg << ' ';
      }
      std::cerr << '\n';

      std::cerr << "ith: " << i << '\n';

      std::cerr << ss << ' ';
      for (auto id : s_ids) {
        std::cerr << id << ' ';
      }
      std::cerr << '\n';

      std::cerr << ff << ' ';
      for (auto id : f_ids) {
        std::cerr << id << ' ';
      }
      std::cerr << '\n';
      return false;
    }
  }
  return true;
}

int main() {
  for (int i = 0; i < 1000; ++i) {
    std::system("./gen");
    std::system("./slow");
    std::system("./fast");
    if (!check()) break;
    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(150ms);
    std::cout << "done " << i << std::endl;
  }
}