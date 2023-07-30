#include "OrderBook.h"

bool OrderBook::is_empty() const {
    return bids.empty() && asks.empty();
}