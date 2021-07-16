#ifndef MARKETSIMULATION_PRODUCT_H
#define MARKETSIMULATION_PRODUCT_H

#include <atomic>
#include <string>

namespace poler::market {
    struct Product {
        Product(uint32_t id, std::string name, double price)
            : id(id), name(std::move(name)), price(price) {}
        const uint32_t id;
        const std::string name;
        std::atomic<double> price;

        std::atomic_int32_t demand = 0;
        std::atomic_int32_t supply = 0;
        std::atomic_int32_t trend = 0;
        std::atomic_int32_t surplus = 0;
    };
}

#endif //MARKETSIMULATION_PRODUCT_H
