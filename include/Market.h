#ifndef MARKETSIMULATION_MARKET_H
#define MARKETSIMULATION_MARKET_H

#include <memory>

#include "Product.h"

namespace poler::market {
    class Market {
    public:
        bool requestItem(std::shared_ptr<Product> product, double& money);
    private:
    };
}

#endif //MARKETSIMULATION_MARKET_H
