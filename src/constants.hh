#ifndef CONSTANTS_HH
#define CONSTANTS_HH

namespace fmk {
    constexpr double STRAWBERRY_WATER_FACTOR = 2.0;
    constexpr double BANANA_WATER_FACTOR     = 1.0;
    constexpr double WATERMELON_WATER_FACTOR = 0.5;

    constexpr int STRAWBERRY_SPOILAGE_FACTOR = 1;
    constexpr int BANANA_SPOILAGE_FACTOR     = 2;
    constexpr int WATERMELON_SPOILAGE_FACTOR = 3;

    constexpr double STRAWBERRY_PRICE_FACTOR = 0.5;
    constexpr double BANANA_PRICE_FACTOR     = 1;
    constexpr double WATERMELON_PRICE_FACTOR = 2.0;

    constexpr double FARMER_STARTING_CASH = 100.0;

    constexpr double COST_PER_WATER_UNIT = 5.0;

    constexpr double ILL_WEIGHT_RATIO = 1.0 / 5.0;
    constexpr double ILL_WATER_RATIO  = 3;
}

#endif //CONSTANTS_HH
