cmake_minimum_required(VERSION 3.20)
project(competitive_programming)

set(CMAKE_CXX_STANDARD 20)

# find_package(nlohmann_json 3.2.0 REQUIRED)

add_definitions(-DLOCAL)

include_directories(.)

#codeforces
add_executable(codeforces_div2 codeforces/div2/152/main.cpp)
add_executable(codeforces_div3 codeforces/div3/903/main.cpp)
add_executable(codeforces_div4 codeforces/div4/898/main.cpp)
add_executable(virtual codeforces/archive/virtual/529/main.cpp)
add_executable(probelmset codeforces/archive/problemset/161D.cpp)
add_executable(edu cf_edu/itmo/dsu/1/C.cpp)
add_executable(kfu codeforces/archive/403347/J.cpp)
add_executable(special codeforces/special/hello_2023/main.cpp)

#codechef
add_executable(codechef codechef/starters/99/main.cpp)

#cses
add_executable(cses cses/AdditionalProblems/main.cpp)

#atcoder
add_executable(atcoder_abc atcoder/abc/351/main.cpp)
add_executable(atcoder_arc atcoder/arc/104/main.cpp)
add_executable(atcoder_dp atcoder/dp_contest/main.cpp)

#stepik
add_executable(stepik stepik/199929/5/5.1.2.cpp)

#temp
add_executable(temp temp.cpp)

#acmp
add_executable(acmp acmp/main.cpp)

#adventofcode
add_executable(adventofcode adventofcode/y2022/main.cpp)

#eolymp
add_executable(eolymp "eolymp/0040[#3-wa].cpp")

#add_executable(yandex_algo yandex_algo_training/main.cpp)

add_executable(timus timus/1133.cpp)

add_executable(uva uva/12003.cpp)

add_executable(rucode "rucode/6.5/c/main.cpp")

add_executable(spoj spoj/main.cpp)

add_executable(projecteuler projecteuler/main.cpp)
# target_link_libraries(projecteuler PRIVATE nlohmann_json::nlohmann_json)

add_subdirectory(${PROJECT_SOURCE_DIR}/stress)