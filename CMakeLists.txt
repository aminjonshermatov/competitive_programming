cmake_minimum_required(VERSION 3.20)
project(competitive_programming)

set(CMAKE_CXX_STANDARD 20)

#codeforces
add_executable(codeforces_div2 codeforces/div2/134/C.cpp)
add_executable(codeforces_div3 codeforces/div3/811/E.cpp)
add_executable(codeforces_div4 codeforces/div4/817/D.cpp)
add_executable(virtual codeforces/archive/virtual/515/D.cpp)
add_executable(probelmset codeforces/archive/problemset/161D.cpp)
add_executable(edu cf_edu/itmo/dsu/1/C.cpp)
add_executable(kfu codeforces/archive/403347/J.cpp)

#codechef
add_executable(codechef codechef/problems/MAXEXP.cpp)

#cses
add_executable(cses cses/GraphAlgorithms/BuildingRoads.cpp)

#atcoder
add_executable(atcoder_abc atcoder/abc/266/C.cpp)

#data structures
add_executable(templates templates/lca.cpp)

#stepik
add_executable(stepik stepik/199929/5/5.1.2.cpp)

#temp
add_executable(temp temp.cpp)

#acmp
add_executable(acmp acmp/119.cpp)
