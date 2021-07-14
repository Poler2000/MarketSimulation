#ifndef MARKETSIMULATION_NEED_H
#define MARKETSIMULATION_NEED_H

#include <memory>

#include "Product.h"

namespace poler::market {
    struct Need {
        std::shared_ptr<Product> product;
        int desire;
    };
}


#endif //MARKETSIMULATION_NEED_H
