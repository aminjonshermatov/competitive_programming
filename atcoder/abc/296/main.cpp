// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<int, ll> pil;
typedef unsigned long long ull;

#define fi first
#define se second
#define P pair
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (ll)(x.size())

#define rep(i, b) for (auto i = 0; i < b; ++i)
#define forr(el, cont) for (auto &el: cont)

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename K, typename V>
using gp_ht = gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>, linear_probe_fn<>, hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<>, true>>;

inline constexpr auto inf = numeric_limits<ll>::max();
inline constexpr auto ninf = numeric_limits<int>::min();
inline constexpr int MOD = 1e9 + 7;
inline const ld pi = ::atan2(0, -1);
inline constexpr ld eps = 1e-6;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

struct Point2d {
  int x, y;
  explicit Point2d(int x_ = 0, int y_ = 0) : x(x_), y(y_) { }

  [[nodiscard]] double len(const Point2d &other) const { return std::sqrt(x * other.x + y * other.y); }
  [[nodiscard]] double angle() const { return std::atan2(y, x); }
  [[nodiscard]] int norm() const { return x * x + y * y; }

  Point2d operator+(const Point2d &other) const { return Point2d{x + other.x, y + other.y}; }
  Point2d operator-(const Point2d &other) const { return Point2d{x - other.x, y - other.y}; }

  bool operator <(const Point2d &other) const { return x == other.x ? y < other.y : x < other.x; }
  bool operator==(const Point2d &other) const { return x == other.x && y == other.y; }

  friend istream& operator>>(istream &in, Point2d &pt) { return in >> pt.x >> pt.y; }
  friend ostream& operator<<(ostream &out, Point2d &pt) { return out << pt.x << ' ' << pt.y; }
};
int dot(const Point2d &a, const Point2d b) {
  // a*b = |a|*|b|*cos(θ) = a.x * b.x + a.y * b.y
  return a.x * b.x + a.y * b.y;
}
int cross(const Point2d &a, const Point2d b) {
  // a^b = |a|*|b|*sin(θ) = a.x * b.y - a.y * b.x
  return a.x * b.y - a.y * b.x;
}

template <typename PointType> struct Line {
  PointType src, dst;
  explicit Line(PointType src_= PointType(), PointType dst_ = PointType()) : src(src_), dst(dst_) { }
};

struct Circle {
  Point2d center;
  int r;
  Circle(Point2d center_, int r_) : center(center_), r(r_) { }
};
using Polygon = vector<Point2d>;

enum class Position : ::int8_t { ONLINE_FRONT, CLOCKWISE, ON_SEGMENT, COUNTER_CLOCKWISE, ONLINE_BACK };
ostream& operator<<(ostream& out, const Position& pos) {
  switch (pos) {
    case Position::ONLINE_FRONT:
      out << "ONLINE_FRONT";
      break ;
    case Position::CLOCKWISE:
      out << "CLOCKWISE";
      break ;
    case Position::ON_SEGMENT:
      out << "ON_SEGMENT";
      break ;
    case Position::COUNTER_CLOCKWISE:
      out << "COUNTER_CLOCKWISE";
      break ;
    case Position::ONLINE_BACK:
      out << "ONLINE_BACK";
      break ;
  }
  return out;
}
enum class Location : ::int8_t { OUT, ON, IN };
ostream& operator<<(ostream& out, const Location& loc) {
  switch (loc) {
    case Location::OUT:
      out << "OUT";
      break ;
    case Location::IN:
      out << "IN";
      break ;
    case Location::ON:
      out << "ON";
      break ;
  }
  return out;
}

Position ccw(const Point2d &a, const Point2d &b) {
  auto crs = cross(a, b);
  if (crs < 0) return Position::CLOCKWISE;
  else if (crs > 0) return Position::COUNTER_CLOCKWISE;
  // vectors are collinear
  if (dot(a, b) < 0) return Position::ONLINE_BACK;
  else if (a.norm() < b.norm()) return Position::ONLINE_FRONT;
  return Position::ON_SEGMENT;
}
Position ccw(const Point2d &a, const Point2d &b, const Point2d &c) { return ccw(b - a, c - a); }
Position ccw(const Line<Point2d> &line, const Point2d &pt) { return ccw(line.src, line.dst, pt); }
bool intersect(const Line<Point2d> &line, const Point2d &pt) { return ccw(line, pt) == Position::ON_SEGMENT; }

Location contain(const Polygon &polygon, const Point2d &pt) {
  bool in = false;
  const int n = static_cast<int>(polygon.size());
  for (int i = 0; i < n; ++i) {
    Line line(polygon[i], polygon[(i + 1) % n]);
    if (intersect(line, pt)) {
      return Location::ON;
    } else {
      auto a = line.src - pt;
      auto b = line.dst - pt;
      if (a.y > b.y) swap(a, b);
      if (a.y <= 0 && b.y > 0 && cross(a, b) > 0) in = !in;
    }
  }
  return in ? Location::IN : Location::OUT;
}

Location convex_contains(const Polygon &polygon, Point2d &pt) {
  assert(!polygon.empty());
  if (polygon[0] == pt) return Location::ON;
  int lo = 0, hi = static_cast<int>(polygon.size());
  while (hi - lo > 1) {
    auto mid = lo + (hi - lo) / 2;
    (ccw(polygon[0], polygon[mid], pt) == Position::CLOCKWISE ? hi : lo) = mid;
  }
  if (hi == 1) return Location::OUT;
  if (lo + 1 == polygon.size()) {
    return intersect(Line(polygon.front(), polygon.back()), pt)
      ? Location::ON
      : Location::OUT;
  }
  if (lo == 1 && intersect(Line(polygon[0], polygon[1]), pt)) return Location::ON;
  Polygon tmp{polygon[0], polygon[lo], polygon[lo + 1]};
  auto res = contain(tmp, pt);
  if (res == Location::ON) {
    return intersect(Line(polygon[lo], polygon[lo + 1]), pt)
      ? Location::ON
      : Location::IN;
  }
  return res;
}

void solve() {
  int n; cin >> n;

  vector<Point2d> polygon(n);
  for (auto &pt : polygon) cin >> pt;

  int q; cin >> q;
  rep(_, q) {
    Point2d pt; cin >> pt;
    cout << convex_contains(polygon, pt) << '\n';
  }
}

//#define MEASURE_TIME
bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#ifdef MEASURE_TIME
  auto start = chrono::steady_clock::now();
#endif
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
#ifdef MEASURE_TIME
  auto finish = chrono::steady_clock::now();
  auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
  cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";
#endif
  return 0;
}
