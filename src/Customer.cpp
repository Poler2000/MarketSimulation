#include <thread>
#include <algorithm>

#include "Customer.h"
#include "Configuration.h"
#include "Random.h"

using namespace std::chrono_literals;

namespace poler::market {
    Customer::Customer(std::string name, std::uint32_t income,
                       std::shared_ptr<Market> market, std::vector<std::shared_ptr<Product>>& products)
        : id_(getId()), name_(std::move(name)), income_(income), isRunning_(true), market_(std::move(market)) {
            for (auto& p : products) {
                needs_[p] = utils::Random::nextInt(10);
            }
    }

    void Customer::run() {
        while(isRunning_) {
            updateNeeds();
            auto wishlist = createWishlist();
            goShopping(wishlist);
            goToSleep();
        }
        utils::Logger::error("customer ends it's journey!");
    }

    std::vector<std::shared_ptr<Product>> Customer::createWishlist() {
        std::vector<std::shared_ptr<Product>> products;
        products.reserve(needs_.size());
        std::map<int, std::shared_ptr<Product>> mapReverse;

        for (const auto& [key, value] : needs_) {
            mapReverse.emplace(value, key);
        }

        for (auto& n: mapReverse) {
            products.emplace_back(n.second);
        }

        return products;
    }

    void Customer::goShopping(std::vector<std::shared_ptr<Product>>& wishlist) {
        double money = income_;
        bool shouldContinueShopping = true;
        utils::Logger::log(std::string(CustomerConfig::dir) + std::to_string(id_), true,
                           "customer goes shopping");

        while (shouldContinueShopping) {
            shouldContinueShopping = false;
            for (const auto& p : wishlist) {
                if (needs_[p] > 0 && market_->buy(p, money)) {
                    needs_[p] = needs_[p] < CustomerConfig::defaultNeedDecrease ? 0 :
                                needs_[p] - CustomerConfig::defaultNeedDecrease;
                    p->demand--;
                    utils::Logger::log(std::string(CustomerConfig::dir) + std::to_string(id_), true,
                                       "customer bought {0} money left: {1}", p->name, money);
                    shouldContinueShopping = true;
                }
                if (money <= 0) {
                    return;
                }
            }
        }

    }

    std::uint32_t Customer::getId() {
        static std::uint32_t idCounter = 1;
        return idCounter++;
    }

    void Customer::goToSleep() {
        std::this_thread::sleep_for(1000ms);
    }

    void Customer::updateNeeds() {
        for (auto& p: needs_) {
            p.second += CustomerConfig::defaultNeedIncrease;
            p.first->demand++;
        }
    }

    void Customer::exit() {
        isRunning_ = false;
    }
}

