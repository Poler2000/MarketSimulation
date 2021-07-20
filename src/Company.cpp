#include <thread>
#include <utility>

#include "Company.h"
#include "Configuration.h"

namespace poler::market {
    Company::Company(std::string name, std::vector<std::shared_ptr<Product>>  products, const double startingFunds)
     : id_(getId()), name_(std::move(name)), isRunning_(true), account_(startingFunds), prevAccount_(account_), products_(std::move(products)) {}

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
            checkStrategy();
            makeChanges();
            displayInfo();
            sleep();
        }
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
    }

    void Company::checkStrategy() {

    }

    void Company::makeChanges() {

    }

    void Company::displayInfo() {
        utils::Logger::info("Company: {0}, id: {1}\n"
                            "in account: {2}, balance: {3}\n"
                            "number of factories: {4}, strategy: {5}\n" ,
                            name_, (int)id_, (double)account_, balance_, (int)factories_.size(), 0);
    }
}