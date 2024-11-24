#ifndef CONSTANTS_HH
#define CONSTANTS_HH

namespace fmk { namespace constants {
    // Fruits //

    constexpr double STRAWBERRY_WEIGHT_FACTOR = 1;
    constexpr double ELDERBERRY_WEIGHT_FACTOR = 1;
    constexpr double WATERMELON_WEIGHT_FACTOR = 1;

    constexpr double STRAWBERRY_WATER_FACTOR = 1;
    constexpr double ELDERBERRY_WATER_FACTOR = 1;
    constexpr double WATERMELON_WATER_FACTOR = 1;

    constexpr double STRAWBERRY_SPOILING_FACTOR = 1;
    constexpr double ELDERBERRY_SPOILING_FACTOR = 1;
    constexpr double WATERMELON_SPOILING_FACTOR = 1;

    constexpr double STRAWBERRY_ILL_UPPER_BOUND = 1;
    constexpr double ELDERBERRY_ILL_UPPER_BOUND = 1;
    constexpr double WATERMELON_ILL_UPPER_BOUND = 1;

    constexpr double STRAWBERRY_ILL_LOWER_BOUND = 1;
    constexpr double ELDERBERRY_ILL_LOWER_BOUND = 1;
    constexpr double WATERMELON_ILL_LOWER_BOUND = 1;

    constexpr double ILL_WEIGHT_RATIO = 1.0 / 5.0;
    constexpr double ILL_WATER_RATIO  = 3;

    constexpr double QUALITY_BONUS = 15.0;

    // Financial //

    constexpr double STRAWBERRY_PRICE_FACTOR = 60;
    constexpr double ELDERBERRY_PRICE_FACTOR = 120;
    constexpr double WATERMELON_PRICE_FACTOR = 240;

    constexpr double COST_PER_WATER_UNIT = 5.0;

    constexpr double ELDERBERRY_FARM_COST = 1000.0;
    constexpr double WATERMELON_FARM_COST = 12000.0;
    constexpr double BEST_FARMER_COST     = 100000.0;

    constexpr double FARMER_STARTING_CASH = 100.0;

    // Requests //

    constexpr int MIN_REQUEST_DAYS = 3;
    constexpr int MAX_REQUEST_DAYS = 15;

    constexpr double MIN_REQUEST_WEIGHT = 0.5;
    constexpr double MAX_REQUEST_WEIGHT = 100.0;

    constexpr double SUCCESSFUL_REQUEST_BONUS = 2500.0;
}}

#endif //CONSTANTS_HH
