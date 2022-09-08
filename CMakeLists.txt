cmake_minimum_required(VERSION 3.20)
project(competitive_programming)

set(CMAKE_CXX_STANDARD 17)

#codeforces
add_executable(codeforces_div2 codeforces/div2/134/C.cpp)
add_executable(codeforces_div3 codeforces/div3/811/E.cpp)
add_executable(codeforces_div4 codeforces/div4/817/D.cpp)
add_executable(archive codeforces/archive/1637/B.cpp)

#codechef
#add_executable(codechef_starters codechef/starters/50/A.cpp)

#cses
add_executable(cses cses/DynamicProgramming/ArrayDescription.cpp)

#atcoder
add_executable(atcoder_abc atcoder/abc/266/C.cpp)

#data structures
add_executable(ds data_structures/main.cpp)

#stepik
add_executable(stepik stepik/112246/2/2.2.4.cpp)
