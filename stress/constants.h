//
// Created by aminjon on 4/13/23.
//
#pragma once

#include <filesystem>

namespace constants {

const std::filesystem::path STRESS_DIR("/home/aminjon/edu/competitive_programming/stress");
const std::filesystem::path DATA_IN(STRESS_DIR / "data.in");
const std::filesystem::path SLOW_OUT(STRESS_DIR / "slow.out");
const std::filesystem::path FAST_OUT(STRESS_DIR / "fast.out");

} // namespace constants