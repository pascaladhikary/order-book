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

TEST(OrderBookTests, LimitOrder) {
    OrderBook book;
    book.add_bid(50, 100);
    book.add_ask(70, 100);

    EXPECT_FALSE(book.buy(70, 110, true));
    EXPECT_TRUE(book.buy(70, 100, true));

    EXPECT_FALSE(book.sell(50, 110, true));
    EXPECT_TRUE(book.sell(50, 100, true));

    EXPECT_TRUE(book.is_empty());
}

TEST(OrderBookTests, MarketOrder) {
    OrderBook book;
    book.add_bid(50, 100);
    book.add_ask(70, 100);
    book.add_ask(75, 75);

    EXPECT_FALSE(book.buy(-1, 176, false));
    EXPECT_TRUE(book.buy(-1, 175, false));

    EXPECT_FALSE(book.sell(-1, 110, false));
    EXPECT_TRUE(book.sell(-1, 100, false));

    EXPECT_TRUE(book.is_empty());
}