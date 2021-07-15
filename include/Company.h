#ifndef MARKETSIMULATION_COMPANY_H
#define MARKETSIMULATION_COMPANY_H

#include <memory>
#include <vector>

#include "Product.h"

namespace poler::market {
    class Company {
        Company(std::string name, std::vector<std::shared_ptr<Product>>&);
        bool requestItem(std::shared_ptr<Product> product, double price);
        void run();
    private:
        const uint32_t id_;
        const std::string name_;
        std::vector<std::shared_ptr<Product>> products_;

        static std::uint32_t getId();
    };
}

#endif //MARKETSIMULATION_COMPANY_H
