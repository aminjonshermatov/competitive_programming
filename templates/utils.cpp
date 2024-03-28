//
// Created by aminjon on 3/28/24.
//
#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
template <typename K, typename V, typename Hash = std::hash<K>>
using gp_hash_table = __gnu_pbds::gp_hash_table<K, V, Hash, std::equal_to<K>, __gnu_pbds::direct_mask_range_hashing<>, __gnu_pbds::linear_probe_fn<>, __gnu_pbds::hash_standard_resize_policy<__gnu_pbds::hash_exponential_size_policy<>, __gnu_pbds::hash_load_check_resize_trigger<>, true>>;

struct array_hasher {
  template <typename T, std::size_t N>
  auto operator() (const std::array<T, N>& key) const {
    std::hash<T> hasher;
    size_t result{};
    for (auto&& x : key) {
      result = (result << 1) ^ hasher(x);
    }
    return result;
  }
};
