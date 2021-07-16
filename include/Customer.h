#ifndef MARKETSIMULATION_CUSTOMER_H
#define MARKETSIMULATION_CUSTOMER_H

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "Need.h"
#include "Market.h"

namespace poler::market {
    class Customer {
    public:
        Customer(std::string name, std::uint32_t  income,
                 std::shared_ptr<Market> market, std::vector<std::shared_ptr<Product>>& products);
        void run();
    private:
        const uint32_t id_;
        const std::string name_;
        bool isRunning_{};
        double income_;
        std::shared_ptr<Market> market_;

        std::map<std::shared_ptr<Product>, int> needs_;
        //std::vector<Need> needs_;

        std::vector<std::shared_ptr<Product>> createWishlist();
        void goShopping(std::vector<std::shared_ptr<Product>>& wishlist);

        static std::uint32_t getId();

        static void goToSleep();

        void updateNeeds();
    };
}

#endif //MARKETSIMULATION_CUSTOMER_H
