cmake_minimum_required(VERSION 3.26)
project(SimpleOrderBook)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimpleOrderBook main.cpp)

find_package(Boost 1.82.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(SimpleOrderBook ${Boost_LIBRARIES})

include_directories(OrderBook)

add_subdirectory(OrderBook)
add_subdirectory(OrderBookTests)

target_link_libraries(SimpleOrderBook OrderBook)
