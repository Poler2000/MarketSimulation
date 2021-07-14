cmake_minimum_required(VERSION 3.19)
project(MarketSimulation)

set(CMAKE_CXX_STANDARD 17)

add_executable(MarketSimulation main.cpp src/Product.cpp include/Product.h src/Customer.cpp include/Customer.h src/Simulation.cpp include/Simulation.h src/Company.cpp include/Company.h src/Factory.cpp include/Factory.h src/Market.cpp include/Market.h include/Configuration.h include/Need.h)