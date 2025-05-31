include_directories(.)

add_executable(gen gen.cpp)
add_executable(slow slow.cpp)
add_executable(fast fast.cpp)
add_executable(stress main.cpp)

set(Boost_NO_BOOST_CMAKE ON)
# wtf there're problem with boost@1.88
set(Boost_INCLUDE_DIR "/opt/homebrew/Cellar/boost@1.85/1.85.0_3/include")
set(BOOST_LIBRARYDIR "/opt/homebrew/Cellar/boost@1.85/1.85.0_3/lib")

find_package(Boost REQUIRED COMPONENTS filesystem system)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(stress PRIVATE ${Boost_LIBRARIES})
