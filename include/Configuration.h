#ifndef MARKETSIMULATION_CONFIGURATION_H
#define MARKETSIMULATION_CONFIGURATION_H

namespace poler::market {
    using namespace std::chrono_literals;

    static constexpr struct CustomerConfig {
        static constexpr int defaultNeedIncrease = 1;
        static constexpr int defaultNeedDecrease = 3;
        static constexpr auto interval = 1000ms;
    } customerConfig;

    static constexpr struct MarketConfig {
        static constexpr auto interval = 1000ms;
    } marketConfig;
}

#endif //MARKETSIMULATION_CONFIGURATION_H
