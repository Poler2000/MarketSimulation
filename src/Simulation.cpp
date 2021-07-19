#include <thread>

#include "Simulation.h"
#include "Configuration.h"
#include "Random.h"

namespace poler::market {
    Simulation::Simulation(uint32_t products, uint32_t companies, uint32_t customers)
        : products_(generateProducts(products)) {
        companies_ = generateCompanies(companies, products_);
        market_ = std::make_shared<Market>(products_, companies_);
        customers_ = generateCustomers(customers, products_);
    }

    void Simulation::run(uint32_t time) {
        utils::Logger::info("Simulation Starting!");
        std::vector<std::thread> threads;

        threads.emplace_back([&](){
            market_->run();
        });

        for (auto& comp : companies_) {
            threads.emplace_back([&](){
                comp->run();
            });
        }

        for (auto& cust : customers_) {
            threads.emplace_back([&](){
                cust->run();
            });
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(time));

        for (auto& cust : customers_) {
            cust->exit();
        }

        for (auto& comp : companies_) {
            comp->exit();
        }

        market_->exit();

        for (auto& t : threads) {
                t.join();
        }
    }

    std::vector<std::shared_ptr<Product>> Simulation::generateProducts(uint32_t amount) {
        std::vector<std::shared_ptr<Product>> products;
        products.reserve(amount);

        const auto permutation = utils::Random::generatePermutation(0, productNames.size() - 1);

        double minMoney = MarketConfig::productAvgPrice - MarketConfig::productPriceRandomFactor;
        double maxMoney = MarketConfig::productAvgPrice + MarketConfig::productPriceRandomFactor;

        for (size_t i = 0; i < amount; i++) {
            products.emplace_back(std::make_shared<Product>(i, std::string(productNames[permutation[i]]),
                                                    utils::Random::nextDouble(minMoney, maxMoney)));
        }
        return products;
    }

    std::vector<std::shared_ptr<Company>>
    Simulation::generateCompanies(uint32_t amount, const std::vector<std::shared_ptr<Product>>& products) {
        std::vector<std::shared_ptr<Company>> companies;
        companies.reserve(amount);

        const auto permutation = utils::Random::generatePermutation(0, companyNames.size() - 1);

        double minMoney = MarketConfig::companyAvgMoney - MarketConfig::companyMoneyRandomFactor;
        double maxMoney = MarketConfig::companyAvgMoney + MarketConfig::companyMoneyRandomFactor;

        for (size_t i = 0; i < amount; i++) {
            companies.emplace_back(std::make_shared<Company>(std::string(companyNames[permutation[i]]), products,
                                                                 utils::Random::nextDouble(minMoney, maxMoney)));
        }
        return companies;
    }

    std::vector<std::unique_ptr<Customer>>
    Simulation::generateCustomers(uint32_t amount, std::vector<std::shared_ptr<Product>> products) {
        std::vector<std::unique_ptr<Customer>> customers;
        customers.reserve(amount);

        const auto permutation = utils::Random::generatePermutation(0, customerNames.size() - 1);

        double minMoney = MarketConfig::customerAvgIncome - MarketConfig::customerIncomeRandomFactor;
        double maxMoney = MarketConfig::customerAvgIncome + MarketConfig::customerIncomeRandomFactor;

        for (size_t i = 0; i < amount; i++) {
            customers.emplace_back(std::make_unique<Customer>(std::string(), utils::Random::nextDouble(minMoney, maxMoney),
                                                      market_, products));
        }
        return customers;
    }
}