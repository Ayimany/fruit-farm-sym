#ifndef CONSTANTS_HH
#define CONSTANTS_HH

namespace fmk { namespace constants {
    // Fruits //

    /// The strawberry weight factor
    constexpr double STRAWBERRY_WEIGHT_FACTOR = 0.5;

    /// The elderberry weight factor
    constexpr double ELDERBERRY_WEIGHT_FACTOR = 1;

    /// The watermelon weight factor
    constexpr double WATERMELON_WEIGHT_FACTOR = 1;

    /// The strawberry water factor
    constexpr double STRAWBERRY_WATER_FACTOR = 1;

    /// The elderberry water factor
    constexpr double ELDERBERRY_WATER_FACTOR = 1;

    /// The watermelon water factor
    constexpr double WATERMELON_WATER_FACTOR = 1;

    /// The strawberry water factor
    constexpr double STRAWBERRY_SPOILING_FACTOR = 1;

    /// The elderberry water factor
    constexpr double ELDERBERRY_SPOILING_FACTOR = 1;

    /// The watermelon water factor
    constexpr double WATERMELON_SPOILING_FACTOR = 1;

    /// The lower bound for ill strawberries
    constexpr double STRAWBERRY_ILL_LOWER_BOUND = 1;

    /// The lower bound for ill elderberries
    constexpr double ELDERBERRY_ILL_LOWER_BOUND = 1;

    /// The lower bound for ill watermelons
    constexpr double WATERMELON_ILL_LOWER_BOUND = 1;

    /// The upper bound for ill strawberries
    constexpr double STRAWBERRY_ILL_UPPER_BOUND = 1;

    /// The upper bound for ill elderberries
    constexpr double ELDERBERRY_ILL_UPPER_BOUND = 1;

    /// The upper bound for ill watermelons
    constexpr double WATERMELON_ILL_UPPER_BOUND = 1;

    /// Price bonus per fruit quality
    constexpr double QUALITY_BONUS = 15.0;

    // Financial //

    /// Strawberry price multiplier
    constexpr double STRAWBERRY_PRICE_FACTOR = 60;

    /// Elderberry price multiplier
    constexpr double ELDERBERRY_PRICE_FACTOR = 120;

    /// Watermelon price multiplier
    constexpr double WATERMELON_PRICE_FACTOR = 240;

    /// Water unit cost
    constexpr double COST_PER_WATER_UNIT = 5.0;

    /// Elderberry farm cost
    constexpr double ELDERBERRY_FARM_COST = 1000.0;

    /// Watermelon farm cost
    constexpr double WATERMELON_FARM_COST = 12000.0;

    /// Best Farmer Title farm cost
    constexpr double BEST_FARMER_COST = 100000.0;

    /// Game starting cash
    constexpr double FARMER_STARTING_CASH = 100.0;

    // Requests //

    /// Minimum time for which a request can be active
    constexpr int MIN_REQUEST_DAYS = 3;

    /// Maximum time for which a request can be active
    constexpr int MAX_REQUEST_DAYS = 15;

    /// Minimum weight that a request can ask for
    constexpr double MIN_REQUEST_WEIGHT = 2.5;

    /// Maximum weight that a request can ask for
    constexpr double MAX_REQUEST_WEIGHT = 100.0;

    /// Bonus upon request completion
    constexpr double SUCCESSFUL_REQUEST_BONUS = 2500.0;
}}

#endif //CONSTANTS_HH
