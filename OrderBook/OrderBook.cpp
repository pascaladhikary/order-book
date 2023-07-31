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

std::ostream &operator<<(std::ostream &os, const OrderBook::BidAsk &ba) {
    auto print = [&](const OrderBook::BidAsk::Entry& e, const std::string& text) {
        bool have_value = e.is_initialized();
        if (have_value) {
            auto value = e.get();
            os << value.second << text << "s @ " << value.first;
        } else {
            os << "NO " << text;
        }
    };
    print(ba.bid, "bid");
    os << ", ";
    return os;
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
    return os;
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

void OrderBook::remove_bid(int price, int amount) {
    remove(price, amount, true);
}

void OrderBook::remove_ask(int price, int amount) {
    remove(price, amount, false);
}

void OrderBook::remove(int price, int amount, bool bid) {
    std::map<int, int>& table = bid ? bids : asks;
    auto it = table.find(price);
    if (it != table.end()) {
        it->second -= amount;
        if (it->second == 0) {
            table.erase(it);
        }
    }
}

boost::optional<int> OrderBook::BidAsk::spread() const {
    boost::optional<int> result;
    if (bid.is_initialized() && ask.is_initialized()) {
        result = ask.get().first - bid.get().first;
    }
    return result;
}
