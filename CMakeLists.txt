cmake_minimum_required(VERSION 3.20)
project(competitive_programming)

set(CMAKE_CXX_STANDARD 17)

#codeforces
add_executable(codeforces_div2 codeforces/div2/785/C.cpp)
add_executable(codeforces_div3 codeforces/div3/811/E.cpp)
add_executable(codeforces_div4 codeforces/div4/790/G.cpp)
add_executable(archive codeforces/archive/1637/B.cpp)

#codechef
#add_executable(codechef_starters codechef/starters/50/A.cpp)

#cses
add_executable(cses cses/SortingAndSearching/SubarraySums2.cpp)


