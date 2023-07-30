#include "OrderBook.h"

bool OrderBook::is_empty() const {
    return bids.empty() && asks.empty();
}

void OrderBook::add_bid(int price, int amount) {
    add(price, amount, true);
}

void OrderBook::add_ask(int price, int amount) {
    add(price, amount, false);
}

void OrderBook::add(int price, int amount, bool bid) {
    if (bid) {
        bids[price] += amount;
    } else {
        asks[price] += amount;
    }
}

std::ostream& operator<<(std::ostream& os, const OrderBook& book) {
    if (book.is_empty()) {
        os << "order book empty";
        return os;
    }

    for (auto ask : book.asks) {
        os << ask.first << "\t" << ask.second;
    }
    os << "\n";
    for (auto bid : book.bids) {
        os << bid.first << "\t" << bid.second ;
    }
}

OrderBook::BidAsk OrderBook::get_bid_ask() const {
    BidAsk result;

    auto best_bid = bids.rbegin();
    if (best_bid != bids.rend()) {
        result.bid = *best_bid;
    }

    auto best_ask = asks.begin();
    if (best_ask != asks.end()) {
        result.ask = *best_ask;
    }

    return result;
}