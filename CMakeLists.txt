cmake_minimum_required(VERSION 3.10)
project(MarketSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pthread")
include_directories(include)

find_path(UTILS_INCLUDE_DIR ...)

if((NOT UTILS_INCLUDE_DIR) OR (NOT EXISTS ${UTILS_INCLUDE_DIR}))
        execute_process(COMMAND git submodule update --init -- vendor/cpp_utils
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

        set(UTILS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cpp_utils/include
        CACHE PATH "cpp_utils include directory")

        install(DIRECTORY ${UTILS_INCLUDE_DIR} DESTINATION build)

        add_library(PolerUtils INTERFACE)
        target_include_directories(PolerUtils INTERFACE
        $<BUILD_INTERFACE:${UTILS_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:build>)

        install(TARGETS PolerUtils EXPORT my_export_set DESTINATION build)
        else()
        endif()

include_directories(vendor/cpp_utils/include)

add_subdirectory(vendor/cpp_utils vendor/cpp_utils/cpp_utils_output)

add_executable(MarketSimulation main.cpp include/Product.h src/Customer.cpp include/Customer.h src/Simulation.cpp include/Simulation.h src/Company.cpp include/Company.h include/Factory.h src/Market.cpp include/Market.h include/Configuration.h include/Need.h)
target_link_libraries(MarketSimulation CppUtils)