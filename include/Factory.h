#ifndef MARKETSIMULATION_FACTORY_H
#define MARKETSIMULATION_FACTORY_H

#include <vector>
#include <memory>

#include "Product.h"

namespace poler::market {
    struct Factory {
    public:
        const uint32_t id;
        std::shared_ptr<Product> product;
        double basicCosts;
        double costsPerItem;
        uint32_t production;
    };
}


#endif //MARKETSIMULATION_FACTORY_H
