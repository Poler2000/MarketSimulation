#ifndef MARKETSIMULATION_FACTORY_H
#define MARKETSIMULATION_FACTORY_H

#include <utility>
#include <vector>
#include <memory>

#include "Product.h"

namespace poler::market {
    struct Factory {
    public:
        explicit Factory(std::shared_ptr<Product> product)
            : id(getId()), product(std::move(product)) {}

        const uint32_t id;
        std::shared_ptr<Product> product;
        double basicCosts = 10;
        double costsPerItem = 3;
        uint32_t production = 10;

        static std::uint32_t getId() {
            static uint32_t idCounter = 1;
            return idCounter++;
        }
    };
}

#endif //MARKETSIMULATION_FACTORY_H
