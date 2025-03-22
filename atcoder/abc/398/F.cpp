#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

template <typename...>
struct cat_tuple_type;
template <typename... T, typename... U>
struct cat_tuple_type<std::tuple<T...>, std::tuple<U...>> {
  using type = std::tuple<T..., U...>;
};

template <typename T, size_t N>
struct n_tuple {
  static_assert(N > 0);
  using type = typename cat_tuple_type<std::tuple<T>, typename n_tuple<T, N - 1>::type>::type;
};

template <typename T>
struct n_tuple<T, std::size_t{1}> {
  using type = std::tuple<T>;
};

template <typename T, size_t N>
using n_tuple_t = n_tuple<T, N>::type;

template <auto... Xs>
constexpr void for_values(auto&& f, auto&& x) {
  (f.template operator()<Xs>(x), ...);
}

constexpr auto for_each(auto&& xs, auto&& f) {
  [&]<size_t... Is>(std::index_sequence<Is...>) {
    (for_values<Is>(f, std::get<Is>(xs)), ...);
  }(std::make_index_sequence<std::tuple_size_v<std::decay_t<decltype(xs)>>>{});
}

struct RollingHash {
  static constexpr std::size_t nTimes = 2u;
  static constexpr bool use_std_array = false;

  using T = int;
  using hash_type = std::conditional_t<use_std_array, std::array<T, nTimes>, n_tuple_t<T, nTimes>>;

  static constexpr std::array<T, 10u> mods = {1000000007, 1000150309, 1000300597,
                                              1000450937, 1000601171, 1000751471,
                                              1000901723, 1001052037, 1001202337,
                                              1001352593};
  static constexpr std::array<T, 10u> bases = {9383, 886, 2777, 6915, 7793, 8335, 5386,
                                               492, 6649, 1421};

  static_assert(mods.size() == bases.size(), "Mismatch `mods` and `bases` length");
  static_assert(0 < nTimes && nTimes <= mods.size(), "`nTimes` not in range [1, |mods|]");

  static std::array<std::size_t, nTimes> selectedIds;
  static bool initializedModsAndBases;

  static std::vector<hash_type> powerOfBases;
  std::vector<hash_type> hashes;

  RollingHash() = default;

  explicit RollingHash(std::string_view s) { init(s); }

  void init(std::string_view s) {
    if (!initializedModsAndBases) {
      initModsAndBases();
    }
    ensure_size(s.size());

    hashes.clear();
    hashes.reserve(s.size());
    hash_type cur{};
    for_each(cur, []<std::size_t>(auto& a) { a = T{}; });
    for (std::size_t i{}; i < s.size(); ++i) {
      for_each(cur, [&]<std::size_t j>(auto&& a) {
        a = add(mul(a, bases[selectedIds[j]], j), ord(s[i]), j);
      });
      hashes.emplace_back(cur);
    }
  }

  [[nodiscard]] hash_type operator()(std::size_t l, std::size_t r) const {
    assert(std::size_t{} <= l && l <= r && r < hashes.size());
    auto ret = hashes[r];
    if (l > std::size_t{}) {
      for_each(ret, [&]<std::size_t j>(auto&& a) {
        a = sub(a, mul(std::get<j>(hashes[l - 1]), std::get<j>(powerOfBases[r - l + 1]), j), j);
      });
    }
    return ret;
  }

  static void initModsAndBases() {
    initializedModsAndBases = true;

    std::random_device rd{};
    std::mt19937 rng(rd());
    std::vector<std::size_t> ids(mods.size());
    std::iota(ids.begin(), ids.end(), std::size_t{});
    std::shuffle(ids.begin(), ids.end(), rng);
    for (std::size_t i{}; i < nTimes; ++i) {
      selectedIds[i] = ids[i];
    }
  }

  static void ensure_size(std::size_t size) {
    if (powerOfBases.empty()) {
      powerOfBases.emplace_back();
      for_each(powerOfBases.back(), []<int i>(auto& a) { a = T{1}; });
    }
    for (; powerOfBases.size() <= size;) {
      powerOfBases.emplace_back();
      for_each(powerOfBases.back(), []<int i>(auto& a) {
        a = mul(std::get<i>(powerOfBases[powerOfBases.size() - 2]), bases[selectedIds[i]], i);
      });
    }
  }

  [[nodiscard]] static T ord(auto&& ch) noexcept {
    return ch - '\0' + 69;
  }

  [[nodiscard]] static T add(const T& a, const T& b, std::size_t which) {
    auto ret = a + b;
    if (ret >= mods[selectedIds[which]]) {
      ret -= mods[selectedIds[which]];
    }
    return ret;
  }

  [[nodiscard]] static T sub(const T& a, const T& b, std::size_t which) {
    auto ret = a - b;
    if (ret < 0) {
      ret += mods[selectedIds[which]];
    }
    return ret;
  }

  [[nodiscard]] static T mul(const T& a, const T& b, std::size_t which) {
    auto ret = a * 1LL * b % mods[selectedIds[which]];
    if (ret < 0) {
      ret += mods[selectedIds[which]];
    }
    return static_cast<int>(ret);
  }
};

bool RollingHash::initializedModsAndBases = false;
std::vector<RollingHash::hash_type> RollingHash::powerOfBases;
std::array<std::size_t, RollingHash::nTimes> RollingHash::selectedIds;

void Solve() {
  std::string s;
  Scan(s);
  const auto n = int(s.size());

  RollingHash sf(s);
  std::ranges::reverse(s);
  RollingHash sb(s);
  std::ranges::reverse(s);

  auto bestLen = 0;
  for (int len = 1; len <= n; ++len) {
    if (sf(n - len, n - 1) == sb(n - (n - 1) - 1, n - (n - len) - 1)) {
      bestLen = len;
    }
  }
  std::string pf;
  if (bestLen != n) {
    pf = s.substr(0, n - bestLen);
  }
  auto ret = pf;
  if (bestLen != 0) {
    ret.append(s.substr(n - bestLen, bestLen));
  }
  std::ranges::reverse(pf);
  ret.append(pf);
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
