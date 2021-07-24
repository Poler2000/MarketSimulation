#include "Simulation.h"
#include <sstream>

int main(int argc, char* argv[]) {\
    constexpr std::string_view msg = "Incorrect arguments! Usage: ./MarketSimulation $products $companies $customers "
                           "where all values should be positive integers\n";
    if (argc != 4) {
        std::cout << msg;
        return 0;
    }

    std::stringstream prod(argv[1]);
    std::stringstream comp(argv[2]);
    std::stringstream cust(argv[3]);

    uint32_t products = 0;
    uint32_t companies = 0;
    uint32_t customers = 0;

    try {
        products = std::stoi(argv[1]);
        companies = std::stoi(argv[2]);
        customers = std::stoi(argv[3]);

    } catch (...) {
        std::cout << msg;
        return 0;
    }

    poler::market::Simulation sim{products, companies, customers};
    sim.run(5000);
    return 0;
}
