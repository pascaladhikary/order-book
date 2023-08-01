#include "OrderBook.h"

bool OrderBook::is_empty() const {
    return bids_.empty() && asks_.empty();
}

void OrderBook::add_bid(int price, int amount) {
    add(price, amount, true);
}

void OrderBook::add_ask(int price, int amount) {
    add(price, amount, false);
}

void OrderBook::add(int price, int amount, bool bid) {
    if (bid) {
        bids_[price] += amount;
    } else {
        asks_[price] += amount;
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

    for (auto ask : book.asks_) {
        os << ask.first << "\t" << ask.second;
    }
    os << "\n";
    for (auto bid : book.bids_) {
        os << bid.first << "\t" << bid.second ;
    }
    return os;
}

OrderBook::BidAsk OrderBook::get_bid_ask() const {
    BidAsk result;

    auto best_bid = bids_.rbegin();
    if (best_bid != bids_.rend()) {
        result.bid = *best_bid;
    }

    auto best_ask = asks_.begin();
    if (best_ask != asks_.end()) {
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
    std::map<int, int>& table = bid ? bids_ : asks_;
    auto it = table.find(price);
    if (it != table.end()) {
        it->second -= amount;
        if (it->second == 0) {
            table.erase(it);
        }
    }
}

bool OrderBook::buy(int price, int amount, bool limit) {
    return limit ? limit_order(price, amount, true) : market_order(price, amount, false);
}

bool OrderBook::sell(int price, int amount, bool limit) {
    return limit ? limit_order(price, amount, false) : market_order(price, amount, false);
}

bool OrderBook::limit_order(int price, int amount, bool buy) {
    std::map<int, int>& table = buy ? asks_ : bids_;

    auto it = table.find(price);
    if (it != table.end() && it->second >= amount) {
        buy ? remove_ask(price, amount) : remove_bid(price, amount);
        return true;
    }
    return false;
}

bool OrderBook::market_order(int price, int amount, bool buy) {

}

boost::optional<int> OrderBook::BidAsk::spread() const {
    boost::optional<int> result;
    if (bid.is_initialized() && ask.is_initialized()) {
        result = ask.get().first - bid.get().first;
    }
    return result;
}
