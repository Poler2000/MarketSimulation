#include <thread>
#include <algorithm>

#include "../include/Customer.h"
#include "../include/Configuration.h"

using namespace std::chrono_literals;

namespace poler::market {
    Customer::Customer(std::string name, std::uint32_t income, std::shared_ptr<Market> market)
        : id_(getId()), name_(std::move(name)), income_(income), isRunning_(true), market_(market) {

    }

    void Customer::run() {
        while(isRunning_) {
            updateNeeds();
            auto wishlist = createWishlist();
            goShopping(wishlist);
            goToSleep();
        }
    }

    std::vector<std::shared_ptr<Product>> Customer::createWishlist() {
        std::vector<std::shared_ptr<Product>> products(needs_.size());
        std::map<int, std::shared_ptr<Product>> mapReverse;

        /*static const auto cmp = [](std::pair<std::shared_ptr<Product>, int> const& a,
                std::pair<std::shared_ptr<Product>,int> const& b) {
            return a.second < b.second;
        };

        std::sort(needs_.begin(), needs_.end(), cmp);*/

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

        for (const auto& p : wishlist) {
            if(market_->requestItem(p, money)) {
                needs_[p] = needs_[p] < customerConfig.defaultNeedDecrease ? 0 :
                        needs_[p] - customerConfig.defaultNeedDecrease;
            }
            if (money <= 0) {
                return;
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
            p.second += customerConfig.defaultNeedIncrease;
        }
    }
}

