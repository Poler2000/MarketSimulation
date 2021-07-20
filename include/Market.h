#ifndef MARKETSIMULATION_MARKET_H
#define MARKETSIMULATION_MARKET_H

#include <memory>
#include <vector>

#include "Product.h"
#include "Company.h"

namespace poler::market {

    class Market {
    public:
        Market(std::vector<std::shared_ptr<Product>>  products,
               std::vector<std::shared_ptr<Company>>  companies);
        void run();
        void exit();
        bool buy(const std::shared_ptr<Product>& product, double& money);
    private:
        static void sleep();
        std::vector<std::shared_ptr<Product>> products_;
        std::vector<std::shared_ptr<Company>> companies_;
        std::atomic_bool isRunning_ = false;

        static void calculateSurplus(const std::shared_ptr<Product> &p) ;

        static void adjustPrice(const std::shared_ptr<Product> &p) ;
    };
}

#endif //MARKETSIMULATION_MARKET_H
