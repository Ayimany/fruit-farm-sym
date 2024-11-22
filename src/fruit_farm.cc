#include "fruit_farm.hh"

#include <cmath>
#include <iostream>

#include "constants.hh"

namespace fmk {
    auto
    calculate_fruit_weight(
        const double water_units,
        const int    days_to_grow,
        const double water_factor
    ) noexcept
        -> double {
        return (water_factor * water_units) / static_cast<double>(days_to_grow);
    }

    auto
    calculate_spoiling_penalty(
        const double weight
    ) noexcept
        -> int {
        return static_cast<int>(std::round(weight / 2.0));
    }

    auto
    calculate_days_to_spoil(
        const int    days_to_grow,
        const double weight,
        double const spoilage_factor
    ) noexcept
        -> int {
        const double penalty = calculate_spoiling_penalty(weight);
        return static_cast<int>(std::round(
            spoilage_factor * days_to_grow - penalty
        ));
    }

    strawberry_farm::strawberry_farm() = default;

    void
    strawberry_farm::grow_strawberry(
        const double water_units,
        const int    days_to_grow
    ) {
        const double weight = calculate_fruit_weight(
            water_units,
            days_to_grow,
            STRAWBERRY_WATER_FACTOR
        );
        const int days_to_spoil = calculate_days_to_spoil(
            days_to_grow,
            weight,
            STRAWBERRY_SPOILAGE_FACTOR
        );

        _storage.emplace(days_to_grow, days_to_spoil, weight);
    }

    double
    strawberry_farm::calculate_strawberry_price(strawberry const &fruit) const {
        return calculate_generic_fruit_price(fruit) * _cost_inflation *
               STRAWBERRY_PRICE_FACTOR;
    }

    double
    strawberry_farm::sell_strawberry(const size_t index) {
        strawberry const &fruit = _storage[index];
        double const      price = calculate_strawberry_price(fruit);
        _storage.remove(index);
        return price;
    }

    banana_farm::banana_farm() = default;

    void
    banana_farm::grow_banana(const double water_units, const int days_to_grow) {
        const double weight = calculate_fruit_weight(
            water_units,
            days_to_grow,
            BANANA_WATER_FACTOR
        );
        const int days_to_spoil = calculate_days_to_spoil(
            days_to_grow,
            weight,
            BANANA_SPOILAGE_FACTOR
        );

        _storage.emplace(days_to_grow, days_to_spoil, weight);
    }

    double
    banana_farm::calculate_banana_price(banana const &fruit) const {
        return calculate_generic_fruit_price(fruit) * _cost_inflation *
               BANANA_PRICE_FACTOR;
    }

    double
    banana_farm::sell_banana(const size_t index) {
        banana const &fruit = _storage[index];
        double const  price = calculate_banana_price(fruit);
        _storage.remove(index);
        return price;
    }

    watermelon_farm::watermelon_farm() = default;

    void
    watermelon_farm::grow_watermelon(
        const double water_units,
        const int    days_to_grow
    ) {
        const double weight = calculate_fruit_weight(
            water_units,
            days_to_grow,
            WATERMELON_WATER_FACTOR
        );
        const int days_to_spoil = calculate_days_to_spoil(
            days_to_grow,
            weight,
            WATERMELON_SPOILAGE_FACTOR
        );

        _storage.emplace(days_to_grow, days_to_spoil, weight);
    }

    double
    watermelon_farm::calculate_watermelon_price(watermelon const &fruit) const {
        return calculate_generic_fruit_price(fruit) * _cost_inflation *
               WATERMELON_PRICE_FACTOR;
    }

    double
    watermelon_farm::sell_watermelon(const size_t index) {
        watermelon const &fruit = _storage[index];
        double const      price = calculate_watermelon_price(fruit);
        _storage.remove(index);
        return price;
    }
}
