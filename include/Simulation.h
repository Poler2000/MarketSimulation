#ifndef MARKETSIMULATION_SIMULATION_H
#define MARKETSIMULATION_SIMULATION_H

#include "Product.h"
#include "Market.h"
#include "Customer.h"

namespace poler::market {
    class Simulation {
    public:
        Simulation(uint32_t products, uint32_t companies, uint32_t customers);
        void run( uint32_t time);

    private:
        std::vector<std::shared_ptr<Product>> products_;
        std::vector<std::shared_ptr<Company>> companies_;
        std::vector<std::unique_ptr<Customer>> customers_;
        std::shared_ptr<Market> market_;

        static std::vector<std::shared_ptr<Product>> generateProducts(uint32_t amount);
        static std::vector<std::shared_ptr<Company>> generateCompanies(uint32_t amount, std::vector<std::shared_ptr<Product>> products);
        std::vector<std::unique_ptr<Customer>> generateCustomers(uint32_t amount, std::vector<std::shared_ptr<Product>> products);
    };
}

#endif //MARKETSIMULATION_SIMULATION_H