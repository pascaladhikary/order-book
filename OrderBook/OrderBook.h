#pragma once
#include <map>

class OrderBook {
    // price, # to be bought/sold at
    std::map<int, int> bids, asks;
public:
    bool is_empty() const;


};