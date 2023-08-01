#pragma once
#include <map>
#include <iostream>
#include <boost/optional.hpp>

class OrderBook {
    // price, # to be bought/sold at
    std::map<int, int> bids_, asks_;
    void add(int price, int amount, bool bid);
    void remove(int price, int amount, bool bid);
    bool limit_order(int price, int amount, bool buy);
    bool market_order(int price, int amount, bool buy);

public:
    struct BidAsk {
        typedef boost::optional<std::pair<int, int>> Entry;
        Entry bid, ask;
        [[nodiscard]] boost::optional<int> spread() const;
    };

    [[nodiscard]] bool is_empty() const;
    void add_bid(int price, int amount);
    void add_ask(int price, int amount);
    void remove_bid(int price, int amount);
    void remove_ask(int price, int amount);
    bool buy(int price, int amount, bool limit);
    bool sell(int price, int amount, bool limit);

    [[nodiscard]] BidAsk get_bid_ask() const;

    friend std::ostream& operator<<(std::ostream& os, const OrderBook& book);
    friend std::ostream& operator<<(std::ostream& os, const OrderBook::BidAsk& ba);
};