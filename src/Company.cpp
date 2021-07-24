#include <thread>
#include <utility>
#include <algorithm>

#include "Company.h"
#include "Configuration.h"
#include "Random.h"

namespace poler::market {
    Company::Company(std::string name, std::vector<std::shared_ptr<Product>>  products, const double startingFunds)
     : id_(getId()), name_(std::move(name)), isRunning_(true), account_(startingFunds),
     currentStrategy_(Strategies::InvestRandomly), prevAccount_(account_), products_(std::move(products)) {}

    bool Company::requestItem(const std::shared_ptr<Product>& product, double price) {
        std::scoped_lock lock(stockMtx_);
        if (stock_[product] > 0) {
            stock_[product]--;
            account_ = account_ + price;
            return true;
        }
        return false;
    }

    void Company::run() {
        utils::Logger::info("Company {0} has started!", name_);

        while (isRunning_) {
            getProducedItems();
            payTheBills();
            recalculateState();
            if (!isRunning_) {
                return;
            }
            checkStrategy();
            makeChanges();
            displayInfo();
            sleep();
        }
        utils::Logger::error("company ends it's journey!");
    }

    uint32_t Company::getId() {
        static uint32_t idCounter = 1;
        return idCounter++;
    }

    void Company::exit() {
        isRunning_ = false;
    }

    void Company::sleep() {
        std::this_thread::sleep_for(CompanyConfig::interval);
    }

    void Company::getProducedItems() {
        stockMtx_.lock();
        for (const auto& f: factories_) {
            stock_[f->product] = std::min(CompanyConfig::maxStock,
                                          stock_[f->product] + f->production);
            f->product->supply += f->production;
        }
        stockMtx_.unlock();
    }

    void Company::payTheBills() {
        account_ = account_ - CompanyConfig::basicDailyCosts;
        for (const auto& f: factories_) {
            account_ = account_ - (f->basicCosts + f->production * f->costsPerItem);
        }
    }

    void Company::recalculateState() {
        balance_ = account_ - prevAccount_;
        prevAccount_ = account_;
        if (account_ < 0 && balance_ < 0) {
            utils::Logger::log(std::string(CompanyConfig::dir) + std::to_string(id_),
                               true, "bankrupt!");
            exit();
        }
    }

    void Company::checkStrategy() {
        if (account_ + balance_ < 0) {
            currentStrategy_ = Strategies::RegainProfitability;
            return;
        }

        if (utils::Random::nextDouble() < CompanyConfig::probabilityOfStrategyChange) {
            currentStrategy_ = static_cast<Strategies>(utils::Random::nextInt(4));
        }
    }

    void Company::makeChanges() {
        switch (currentStrategy_) {
            case Strategies::InvestInHighDemand:
                checkForHighDemand();
                break;
            case Strategies::InvestInHighPrice:
                checkForHighPrice();
                break;
            case Strategies::InvestRandomly:
                makeRandomInvestment();
                break;
            case Strategies::MakeNoChanges:
                break;
            case Strategies::RegainProfitability:
                regainProfitability();
                break;
        }
    }

    void Company::displayInfo() {
        utils::Logger::info("Company: {0}, id: {1}\n"
                            "in account: {2}, balance: {3}\n"
                            "number of factories: {4}, strategy: {5}\n" ,
                            name_, (int)id_, (double)account_, balance_, (int)factories_.size(), 0);
        utils::Logger::log(std::string(CompanyConfig::dir) + std::to_string(id_),
                           true, "in account: {0}, balance: {1}\n number of factories: {2}, strategy: {3}",
                           (double)account_, balance_, (int)factories_.size(), (int)currentStrategy_);
    }

    void Company::checkForHighDemand() {
        if (account_ + balance_ - CompanyConfig::newFactoryCosts > 0) {
            auto itMax = std::max_element(products_.begin(), products_.end(), [](const auto& p, const auto& q) {
                return p->demand < q->demand;
            });
            utils::Logger::log(std::string(CompanyConfig::dir) + std::to_string(id_), true, "new factory: {}", itMax->get()->name);
            factories_.emplace_back(std::make_unique<Factory>(*itMax));
        }
    }

    void Company::checkForHighPrice() {
        if (account_ + balance_ - CompanyConfig::newFactoryCosts > 0) {
            auto itMax = std::max_element(products_.begin(), products_.end(), [](const auto& p, const auto& q) {
                return p->price < q->price;
            });
            utils::Logger::log(std::string(CompanyConfig::dir) + std::to_string(id_), true, "new factory: {}", itMax->get()->name);
            factories_.emplace_back(std::make_unique<Factory>(*itMax));
        }
    }

    void Company::makeRandomInvestment() {
        if (account_ + balance_ - CompanyConfig::newFactoryCosts > 0) {
            auto& p = products_[utils::Random::nextInt((int)products_.size())];
            utils::Logger::log(std::string(CompanyConfig::dir) + std::to_string(id_), true, "new factory: {}", p->name);
            factories_.emplace_back(std::make_unique<Factory>(p));
        }
    }

    void Company::regainProfitability() {
        for (auto& f : factories_) {
            if (f->basicCosts + f->costsPerItem * f->production >
                f->product->price * f->production) {
                f.reset();
                account_ = account_ + CompanyConfig::factorySellPrice;
                continue;
            }
            if ((double)f->product->supply / f->product->demand > CompanyConfig::dangerousSDRatio) {
                f.reset();
                account_ = account_ + CompanyConfig::factorySellPrice;
            }
        }

        factories_.erase(
                std::remove(factories_.begin(), factories_.end(), nullptr), factories_.end());
    }
}