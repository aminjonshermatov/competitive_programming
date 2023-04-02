cmake_minimum_required(VERSION 3.20)
project(competitive_programming)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DLOCAL)

include_directories(.)

#codeforces
add_executable(codeforces_div2 codeforces/div2/858/main.cpp)
add_executable(codeforces_div3 codeforces/div3/834/D.cpp)
add_executable(codeforces_div4 codeforces/div4/859/main.cpp)
add_executable(virtual codeforces/archive/virtual/529/main.cpp)
add_executable(probelmset codeforces/archive/problemset/161D.cpp)
add_executable(edu cf_edu/itmo/dsu/1/C.cpp)
add_executable(kfu codeforces/archive/403347/J.cpp)
add_executable(special codeforces/special/hello_2023/main.cpp)

#codechef
add_executable(codechef codechef/starters/80/main.cpp)

#cses
add_executable(cses cses/TreeAlgorithms/FindingACentroid.cpp)

#atcoder
add_executable(atcoder_abc atcoder/abc/296/main.cpp)
add_executable(atcoder_arc atcoder/arc/058/main.cpp)
add_executable(atcoder_dp atcoder/dp_contest/main.cpp)

#data structures
add_executable(templates templates/persistent_stack.cpp)

#stepik
add_executable(stepik stepik/199929/5/5.1.2.cpp)

#temp
add_executable(temp temp.cpp)

#acmp
add_executable(acmp acmp/main.cpp)

#adventofcode
add_executable(adventofcode adventofcode/2022/main.cpp)

#eolymp
add_executable(eolymp "eolymp/0040[#3-wa].cpp")

add_executable(yandex_algo yandex_algo_training/main.cpp)

add_executable(timus timus/1133.cpp)

add_executable(uva uva/12003.cpp)

add_executable(rucode "rucode/6.0/d/main.cpp")