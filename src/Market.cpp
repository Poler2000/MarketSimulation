#include <thread>
#include <utility>

#include "Market.h"
#include "Configuration.h"
#include "Random.h"

namespace poler::market {
    Market::Market(std::vector<std::shared_ptr<Product>> products,
                   std::vector<std::shared_ptr<Company>> companies)
                   : products_(std::move(products)), companies_(std::move(companies)) {}

    void Market::run() {
        isRunning_ = true;
        while (isRunning_) {
            sleep();
            for (auto& p : products_) {
                auto newSurplus = p->supply - p->demand;
                p->trend = p->surplus - newSurplus;
                p->surplus = newSurplus;
                p->displayInfo();
            }
        }
    }

    bool Market::buy(const std::shared_ptr<Product>& product, double &money) {
        bool result = false;
        do {
            int i = utils::Random::nextInt(companies_.size() - 1);
            double price = product->price;
            if (money < price) {
                return false;
            }

            result = companies_[i]->requestItem(product, price);
        } while (!result);
        return true;
    }

    void Market::sleep() {
        std::this_thread::sleep_for(MarketConfig::interval);
    }

    void Market::exit() {
        isRunning_ = false;
    }
}

