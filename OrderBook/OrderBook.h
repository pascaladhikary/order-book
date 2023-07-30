#pragma once
#include <map>
#include <iostream>
#include <boost/optional.hpp>

class OrderBook {
    // price, # to be bought/sold at
    std::map<int, int> bids, asks;
    void add(int price, int amount, bool bid);

public:
    struct BidAsk {
        typdef boost::optional<std::pair<int, int>> Entry;
        Entry bid, ask;
        boost::optional<int> spread() const;
    };

    bool is_empty() const;
    void add_bid(int price, int amount);
    void add_ask(int price, int amount);

    BidAsk get_bid_ask() const;

    friend std::ostream& operator<<(std::ostream& os, const OrderBook& book);
};