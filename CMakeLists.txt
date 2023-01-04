cmake_minimum_required(VERSION 3.20)
project(competitive_programming)

set(CMAKE_CXX_STANDARD 20)

#codeforces
add_executable(codeforces_div2 codeforces/div2/134/C.cpp)
add_executable(codeforces_div3 codeforces/div3/834/D.cpp)
add_executable(codeforces_div4 codeforces/div4/817/D.cpp)
add_executable(virtual codeforces/archive/virtual/529/main.cpp)
add_executable(probelmset codeforces/archive/problemset/161D.cpp)
add_executable(edu cf_edu/itmo/dsu/1/C.cpp)
add_executable(kfu codeforces/archive/403347/J.cpp)
add_executable(special codeforces/special/hello_2023/main.cpp)

#codechef
add_executable(codechef codechef/starters/72/main.cpp)

#cses
add_executable(cses cses/GraphAlgorithms/MailDelivery.cpp)

#atcoder
add_executable(atcoder_abc atcoder/abc/274/main.cpp)

#data structures
add_executable(templates templates/persistent_stack.cpp)

#stepik
add_executable(stepik stepik/199929/5/5.1.2.cpp)

#temp
add_executable(temp temp.cpp)

#acmp
add_executable(acmp acmp/119.cpp)

#adventofcode
add_executable(adventofcode adventofcode/2022/main.cpp)

#eolymp
add_executable(eolymp eolymp/1738.cpp)
