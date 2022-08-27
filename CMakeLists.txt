cmake_minimum_required(VERSION 3.20)
project(competitive_programming)

set(CMAKE_CXX_STANDARD 17)

#codeforces
add_executable(codeforces_div2 codeforces/div2/134/C.cpp debug.h)
add_executable(codeforces_div3 codeforces/div3/811/E.cpp debug.h)
add_executable(codeforces_div4 codeforces/div4/790/G.cpp debug.h)
add_executable(archive codeforces/archive/1637/B.cpp debug.h)

#codechef
#add_executable(codechef_starters codechef/starters/50/A.cpp debug.h)

#cses
add_executable(cses cses/SortingAndSearching/MaximumSubarraySum2.cpp debug.h)

#atcoder
add_executable(atcoder_abc atcoder/abc/266/C.cpp)

