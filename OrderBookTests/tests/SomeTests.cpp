#include <gtest/gtest.h>
#include <OrderBook.h>

TEST(OrderBookTests, OrderBookEmptyByDefault)
{
    OrderBook book;
    EXPECT_TRUE(book.is_empty());
};

TEST(OrderBookTests, OrderAddition) {
    OrderBook book;
    book.add_bid(123, 456);
    OrderBook::BidAsk ba = book.get_bid_ask();
    EXPECT_TRUE(ba.bid.is_initialized());

    std::pair<int, int> bid = ba.bid.get();
    EXPECT_EQ(123, bid.first);
    EXPECT_EQ(456, bid.second);
}

TEST (OrderBookTests, OrderRemoval) {
    OrderBook book;
    book.add_bid(123, 456);
    book.remove_bid(123, 156);
    OrderBook::BidAsk ba = book.get_bid_ask();
    EXPECT_TRUE(ba.bid.is_initialized());

    std::pair<int, int> bid = ba.bid.get();
    EXPECT_EQ(123, bid.first);
    EXPECT_EQ(456-156, bid.second);
}

TEST(OrderBookTests, SpreadCalculated) {
    OrderBook book;
    book.add_bid(50, 100);
    book.add_ask(70, 100);
    OrderBook::BidAsk bid_ask = book.get_bid_ask();
    EXPECT_TRUE(bid_ask.bid.is_initialized());
    EXPECT_TRUE(bid_ask.ask.is_initialized());

    boost::optional<int> spread = bid_ask.spread();
    EXPECT_TRUE(spread.is_initialized());
    EXPECT_EQ(20, spread.get());
}