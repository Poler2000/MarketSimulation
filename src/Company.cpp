#include <thread>
#include <utility>

#include "Company.h"
#include "Configuration.h"

namespace poler::market {
    Company::Company(std::string name, std::vector<std::shared_ptr<Product>>  products, const double startingFunds)
     : id_(getId()), name_(std::move(name)), isRunning_(true), account_(startingFunds), products_(std::move(products)) {}

    bool Company::requestItem(const std::shared_ptr<Product>& product, double price) {
        return true;
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

    }

    void Company::payTheBills() {

    }

    void Company::recalculateState() {

    }

    void Company::checkStrategy() {

    }

    void Company::makeChanges() {

    }

    void Company::displayInfo() {
        utils::Logger::info("Company: {0}, id: {1}\n"
                            "in account: {2}, balance: {3}\n"
                            "number of factories: {4}, strategy: {5}\n" ,
                            name_, (int)id_, account_, balance_, (int)factories_.size(), 0);
    }
}