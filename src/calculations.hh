#ifndef CALCULATIONS_HH
#define CALCULATIONS_HH
#include "fruit.hh"

namespace fmk { namespace calc {
    /**
     * Calculates the weight of a fruit
     * @param water_units The amount of water units given
     * @param days_to_grow The days it is allowed to grow
     * @param weight_factor A fruit-specific factor
     * @param water_factor A fruit-specific factor
     *
     * @return The weight of the fruit
     *
     * @note Fruits that have a lot of water in them, such as watermelons,
     * have low water factors because they need more water to grow.
     */
    [[nodiscard]] auto
    fruit_weight(
        int    days_to_grow,
        double water_units,
        double weight_factor,
        double water_factor
    ) noexcept
        -> double;

    /**
     * Calculates the spoiling penalty based on the weight of a fruit, that is
     * a subtraction to the amount of time it takes the fruit to spoil.
     * @param weight The weight of the fruit
     * @return The spoiling penalty
     */
    [[nodiscard]] auto
    spoiling_penalty(
        double weight
    ) noexcept
        -> int;

    /**
     * Calculates the days in which a fruit will spoil
     * @param days_to_grow The days the fruit is allowed to grow
     * @param weight The weight of the fruit
     * @param spoiling_factor A fruit-specific spoilage factor
     * @return The amount of days in which the fruit will spoil
     */
    [[nodiscard]] auto
    days_to_spoil(
        int    days_to_grow,
        double weight,
        double spoiling_factor
    ) noexcept
        -> int;

    /**
     * Calculates the fruit quality factor
     * @return The fruit quality factor
     */
    [[nodiscard]] auto
    fruit_quality(
        int    days_to_grow,
        double water_units
    ) noexcept
        -> double;

    /**
     * Calculates whether a fruit is ill or not.
     * @param days_to_grow The days the fruit is allowed to grow
     * @param water_units The amounf of water units added
     * @param bounds The bounds to clear
     * @return Whether the fruit is ill, or not
     */
    [[nodiscard]] auto
    ill_status(
        int                              days_to_grow,
        double                           water_units,
        const std::pair<double, double> &bounds
    ) noexcept
        -> bool;

    /**
     * Calculates the price of a generic fruit
     * @param fruit The fruit
     * @return The price of the fruit
     */
    [[nodiscard]] auto
    base_fruit_price(
        fruit const &fruit
    ) noexcept
        -> double;

    [[nodiscard]] auto
    supply_demand_penalty(
        size_t fruit_count,
        size_t storage_size
    ) noexcept
        -> double;
}}

#endif //CALCULATIONS_HH
