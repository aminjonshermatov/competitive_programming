cmake_minimum_required(VERSION 3.20)
project(competitive_programming)

# find_package(nlohmann_json 3.2.0 REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_definitions(-DLOCAL)

include_directories(.)
include_directories(/usr/local/include)

#codechef
# add_executable(codechef codechef/starters/99/main.cpp)

#cses
# add_executable(cses cses/AdditionalProblems/main.cpp)

add_subdirectory(${PROJECT_SOURCE_DIR}/atcoder)

#temp
add_executable(temp temp.cpp)

# add_executable(spoj spoj/main.cpp)

# add_executable(projecteuler projecteuler/main.cpp)
# target_link_libraries(projecteuler PRIVATE nlohmann_json::nlohmann_json)

add_subdirectory(${PROJECT_SOURCE_DIR}/stress)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    message(STATUS "Using ccache")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)
