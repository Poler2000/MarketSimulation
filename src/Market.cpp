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
            for (const auto& p : products_) {
                calculateSurplus(p);
                adjustPrice(p);

                p->displayInfo();
            }
        }
    }

    void Market::adjustPrice(const std::shared_ptr<Product> &p) {
        if (p->surplus >= 0) {
            p->price = std::max(MarketConfig::productMinPrice,
                                p->price - utils::Random::nextDouble(MarketConfig::productPriceChange));
        }
        else {
            p->price = p->price + utils::Random::nextDouble(MarketConfig::productPriceChange);
        }
    }

    void Market::calculateSurplus(const std::shared_ptr<Product> &p) {
        auto newSurplus = p->supply - p->demand;
        p->trend = p->surplus - newSurplus;
        p->surplus = newSurplus;
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

