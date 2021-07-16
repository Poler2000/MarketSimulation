#ifndef MARKETSIMULATION_PRODUCT_H
#define MARKETSIMULATION_PRODUCT_H

#include <atomic>
#include <string>

#include "Logger.h"

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

        void displayInfo() const {
            utils::Logger::info("Current state of {0} id: {1}:\n"
                                "current price: {2} \n"
                                "supply: {3}, demand: {4} \n"
                                "trend: {5}, surplus: {6}\n", name, (int)id,
                                double(price), int(supply), int(demand), int(trend), int(surplus));
        }
    };
}

#endif //MARKETSIMULATION_PRODUCT_H
