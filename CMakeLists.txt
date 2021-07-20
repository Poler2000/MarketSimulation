cmake_minimum_required(VERSION 3.19)
project(MarketSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pthread")
include_directories(include)
include_directories(vendor/cpp_utils/include)

add_subdirectory(vendor/cpp_utils vendor/cpp_utils/cpp_utils_output)

add_executable(MarketSimulation main.cpp include/Product.h src/Customer.cpp include/Customer.h src/Simulation.cpp include/Simulation.h src/Company.cpp include/Company.h include/Factory.h src/Market.cpp include/Market.h include/Configuration.h include/Need.h)
target_link_libraries(MarketSimulation CppUtils)