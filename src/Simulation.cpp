#include <thread>

#include "Simulation.h"
#include "Logger.h"

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
        std::vector<std::shared_ptr<Product>> products(amount);
        products[0] = std::make_shared<Product>(1, "Bicycle", 10.0);
        return products;
    }

    std::vector<std::shared_ptr<Company>>
    Simulation::generateCompanies(uint32_t amount, std::vector<std::shared_ptr<Product>> products) {
        std::vector<std::shared_ptr<Company>> companies(amount);
        companies[0] = std::make_shared<Company>("Poler Inc.", products);
        return companies;
    }

    std::vector<std::unique_ptr<Customer>>
    Simulation::generateCustomers(uint32_t amount, std::vector<std::shared_ptr<Product>> products) {
        std::vector<std::unique_ptr<Customer>> customers(amount);
        customers[0] = std::make_unique<Customer>("John", 1000, market_, products);
        return customers;
    }
}