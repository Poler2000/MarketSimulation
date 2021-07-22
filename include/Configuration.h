#ifndef MARKETSIMULATION_CONFIGURATION_H
#define MARKETSIMULATION_CONFIGURATION_H

#include <vector>
#include <array>
#include <string_view>

namespace poler::market {
    using namespace std::chrono_literals;

    static constexpr struct CustomerConfig {
        static constexpr int defaultNeedIncrease = 1;
        static constexpr int defaultNeedDecrease = 3;
        static constexpr auto interval = 100ms;
        static constexpr std::string_view dir = "sim1/customer/";
    } customerConfig;

    static constexpr struct MarketConfig {
        static constexpr auto interval = 100ms;
        static constexpr double companyAvgMoney = 3000;
        static constexpr double companyMoneyRandomFactor = 500;
        static constexpr double customerAvgIncome = 500;
        static constexpr double customerIncomeRandomFactor = 200;
        static constexpr double productAvgPrice = 50;
        static constexpr double productPriceRandomFactor = 30;
        static constexpr double productPriceChange = 5;
        static constexpr double productMinPrice = 0.1;
        static constexpr std::string_view dir = "sim1/product/";
    } marketConfig;

    static constexpr struct CompanyConfig {
        static constexpr auto interval = 100ms;
        static constexpr double basicDailyCosts = 50;
        static constexpr double newFactoryCosts = 100;
        static constexpr uint32_t maxStock = 100;
        static constexpr double probabilityOfStrategyChange = 0.3;
        static constexpr std::string_view dir = "sim1/company/";
    } companyConfig;

    static constexpr std::array<std::string_view , 30> customerNames = {
            "Alex",
            "Alice",
            "Amy",
            "Anna",
            "Anastasia",
            "Bruce",
            "Daniel",
            "Dorothy",
            "Emily",
            "Eliza",
            "George",
            "Gustav",
            "Hans",
            "Harold",
            "Jack",
            "Juan",
            "Julia",
            "Kate",
            "Laura",
            "Martha",
            "Natalie",
            "Nelson",
            "Patrick",
            "Paul",
            "Peter",
            "Pierre",
            "Rachel",
            "Stefan",
            "Veronica",
            "Victoria",
    };

    static constexpr std::array<std::string_view , 20> companyNames = {
            "Poler Inc.",
            "Constantinople Kebab",
            "JSON&Sons",
            "Cucumber Global",
            "Kinky! Interactive",
            "Dream Factory",
            "Wild West Company",
            "Big Bargain Burger",
            "QWERTY",
            "Kochanowski&Daughters",
            "Flying Penguins",
            "Wilhelm's Holdings",
            "Siskin Sisterhood",
            "WolfpackGroup",
            "Ancient Brewery",
            "Literal Heaven",
            "Caesar's ides of March",
            "Well Known Business Group",
            "Laziness Inc.",
            "SpaceY",
    };

    static constexpr std::array<std::string_view, 20> productNames = {
            "Bicycles",
            "Mobile Phones",
            "Cars",
            "Oranges",
            "Beer",
            "Rubber Ducks",
            "Irish Whisky",
            "Programming Books",
            "TV",
            "Wine",
            "Sunglasses",
            "Frozen Chicken",
            "Masks",
            "Headphones",
            "Turkish Carpets",
            "Smart Microwave",
            "Smart Vacuum Cleaner",
            "Smart Fridge",
            "Smart Broom",
            "Wireless Wires",
    };
}

#endif //MARKETSIMULATION_CONFIGURATION_H
