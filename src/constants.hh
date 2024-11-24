#ifndef CONSTANTS_HH
#define CONSTANTS_HH

namespace fmk {
    constexpr double STRAWBERRY_WATER_FACTOR = 0.5;
    constexpr double ELDERBERRY_WATER_FACTOR = 1.0;
    constexpr double WATERMELON_WATER_FACTOR = 2.0;

    constexpr int STRAWBERRY_SPOILAGE_FACTOR = 1;
    constexpr int ELDERBERRY_SPOILAGE_FACTOR = 2;
    constexpr int WATERMELON_SPOILAGE_FACTOR = 3;

    constexpr double STRAWBERRY_PRICE_FACTOR = 60;
    constexpr double ELDERBERRY_PRICE_FACTOR = 120;
    constexpr double WATERMELON_PRICE_FACTOR = 240;

    constexpr double FARMER_STARTING_CASH = 100.0;

    constexpr double COST_PER_WATER_UNIT = 5.0;

    constexpr double ILL_WEIGHT_RATIO = 1.0 / 5.0;
    constexpr double ILL_WATER_RATIO  = 3;

    constexpr double ELDERBERRY_FARM_COST = 1000.0;
    constexpr double WATERMELON_FARM_COST = 12000.0;
    constexpr double BEST_FARMER_COST     = 100000.0;

    constexpr int MIN_REQUEST_DAYS = 3;
    constexpr int MAX_REQUEST_DAYS = 15;

    constexpr double MIN_REQUEST_WEIGHT = 0.5;
    constexpr double MAX_REQUEST_WEIGHT = 100.0;

    constexpr double SUCCESSFUL_REQUEST_BONUS = 2500.0;
    constexpr double QUALITY_BONUS            = 15.0;
}

#endif //CONSTANTS_HH
