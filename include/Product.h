#ifndef MARKETSIMULATION_PRODUCT_H
#define MARKETSIMULATION_PRODUCT_H

#include <atomic>
#include <string>

namespace poler::market {
    struct Product {
        const uint32_t id;
        const std::string name;
        std::atomic<double> price;

        std::atomic_int32_t demand;
        std::atomic_int32_t supply;
        std::atomic_int32_t trend;
        std::atomic_int32_t surplus = 0;
    };
}

#endif //MARKETSIMULATION_PRODUCT_H
