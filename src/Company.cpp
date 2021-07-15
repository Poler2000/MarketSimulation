#include "Company.h"

namespace poler::market {
    Company::Company(std::string name, std::vector<std::shared_ptr<Product>> & products)
     : id_(getId()), name_(std::move(name)), products_(products) {}

    bool Company::requestItem(std::shared_ptr<Product> product, double price) {
        return true;
    }

    void Company::run() {

    }

    uint32_t Company::getId() {
        static uint32_t idCounter = 1;
        return idCounter++;
    }
}