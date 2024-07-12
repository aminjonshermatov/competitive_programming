include_directories(.)

add_executable(gen gen.cpp)
add_executable(slow slow.cpp)
add_executable(fast fast.cpp)
add_executable(stress main.cpp)

find_package(Boost 1.85.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})