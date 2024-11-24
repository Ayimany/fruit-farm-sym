#include "calculations.hh"

#include <cmath>

#include "constants.hh"

namespace fmk { namespace calc {
    auto
    fruit_weight(
        const int    days_to_grow,
        const double water_units,
        const double weight_factor,
        const double water_factor
    ) noexcept
        -> double {
        return water_factor * water_units / static_cast<double>(days_to_grow) *
               weight_factor;
    }

    auto
    spoiling_penalty(
        const double weight
    ) noexcept
        -> int {
        return static_cast<int>(std::round(weight / 2.0));
    }

    auto
    days_to_spoil(
        const int    days_to_grow,
        const double weight,
        double const spoiling_factor
    ) noexcept
        -> int {
        const double penalty = spoiling_penalty(weight);
        return static_cast<int>(std::round(
            spoiling_factor * (days_to_grow - penalty)
        ));
    }

    [[nodiscard]] auto
    fruit_quality(
        const int    days_to_grow,
        const double water_units
    ) noexcept
        -> double {
        return 1.0 + static_cast<double>(days_to_grow) / (2.0 * water_units);
    }

    auto
    ill_status(
        const int                        days_to_grow,
        const double                     water_units,
        const std::pair<double, double> &bounds
    ) noexcept
        -> bool {
        const double r = water_units / static_cast<double>(days_to_grow);
        return r < bounds.first || r > bounds.second;
    }

    auto
    base_fruit_price(
        fruit const &fruit
    ) noexcept
        -> double {
        if (fruit.is_spoiled()) {
            return 0.0;
        }

        return fruit.get_weight() / (fruit.get_days_to_full_growth() + 1);
    }
}}
