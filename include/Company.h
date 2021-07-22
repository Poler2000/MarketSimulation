#ifndef MARKETSIMULATION_COMPANY_H
#define MARKETSIMULATION_COMPANY_H

#include <memory>
#include <vector>
#include <unordered_map>

#include "Product.h"
#include "Factory.h"


namespace poler::market {
    enum class Strategies {
        InvestInHighDemand,
        InvestInHighPrice,
        InvestRandomly,
        MakeNoChanges,
        RegainProfitability,
    };

    class Company {
    public:
        Company(std::string name, std::vector<std::shared_ptr<Product>> products, double startingFunds);
        bool requestItem(const std::shared_ptr<Product>& product, double price);
        void run();
        void exit();

    private:
        const uint32_t id_;
        const std::string name_;
        std::atomic_bool isRunning_;
        std::atomic<double> account_;
        Strategies currentStrategy_;

        double balance_ = 0;
        double prevAccount_ = 0;

        std::vector<std::shared_ptr<Product>> products_;
        std::vector<std::unique_ptr<Factory>> factories_;
        std::unordered_map<std::shared_ptr<Product>, uint32_t> stock_;

        std::mutex stockMtx_;

        static std::uint32_t getId();

        static void sleep();

        void getProducedItems();

        void payTheBills();

        void recalculateState();

        void checkStrategy();

        void makeChanges();

        void displayInfo();

        void checkForHighDemand();

        void checkForHighPrice();

        void makeRandomInvestment();

        void regainProfitability();
    };
}

#endif //MARKETSIMULATION_COMPANY_H
