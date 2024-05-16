include_directories(.)

find_package(Boost REQUIRED)

add_executable(gen gen.cpp)
add_executable(slow slow.cpp)
add_executable(fast fast.cpp)
add_executable(stress main.cpp)