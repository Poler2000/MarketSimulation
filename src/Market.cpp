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
        utils::Logger::error("market ends it's journey!");
    }

    void Market::adjustPrice(const std::shared_ptr<Product> &p) {
        auto prev = (double)p->price;
        if (p->surplus >= 0) {
            p->price = std::max(MarketConfig::productMinPrice,
                                p->price - utils::Random::nextDouble(MarketConfig::productPriceChange));
        }
        else {
            p->price = p->price + utils::Random::nextDouble(MarketConfig::productPriceChange);
        }

        utils::Logger::log(std::string(MarketConfig::dir) + std::to_string(p->id), true,
                           "price from {0} to {1}, demand: {2}, supply {3}", prev, (double)p->price, (int)p->demand, (int)p->surplus);
    }

    void Market::calculateSurplus(const std::shared_ptr<Product> &p) {
        auto newSurplus = p->supply - p->demand;
        p->trend = p->surplus - newSurplus;
        p->surplus = newSurplus;
    }

    bool Market::buy(const std::shared_ptr<Product>& product, double &money) {
        bool result = false;

        const auto permutation = utils::Random::generatePermutation(0, companies_.size() - 1);

        double price = product->price;
        if (money < price) {
            return false;
        }

        for (size_t i = 0; i < companies_.size(); i++) {
            result = companies_[permutation[i]]->requestItem(product, price);
            if (result) {
                money -= price;
                return true;
            }
        }

        return false;
    }

    void Market::sleep() {
        std::this_thread::sleep_for(MarketConfig::interval);
    }

    void Market::exit() {
        isRunning_ = false;
    }
}

