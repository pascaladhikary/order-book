cmake_minimum_required(VERSION 3.26)
project(SimpleOrderBook)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimpleOrderBook main.cpp)

include_directories(OrderBook)

add_subdirectory(OrderBook)
add_subdirectory(OrderBookTests)

target_link_libraries(SimpleOrderBook OrderBook)
