#ifndef MARKETSIMULATION_CONFIGURATION_H
#define MARKETSIMULATION_CONFIGURATION_H

namespace poler::market {
    static constexpr struct CustomerConfig {
        int defaultNeedIncrease = 1;
        int defaultNeedDecrease = 3;
    } customerConfig;
}

#endif //MARKETSIMULATION_CONFIGURATION_H
