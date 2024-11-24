#include "fruit_farm.hh"

#include <cmath>
#include <iostream>

#include "constants.hh"

namespace fmk {
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

        add_fruit(days_to_grow, days_to_spoil, weight);
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

        remove_fruit(index);

        return price;
    }

    elderberry_farm::elderberry_farm() = default;

    void
    elderberry_farm::grow_elderberry(
        const double water_units,
        const int    days_to_grow
    ) {
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

        add_fruit(days_to_grow, days_to_spoil, weight);
    }

    double
    elderberry_farm::calculate_elderberry_price(elderberry const &fruit) const {
        return calculate_generic_fruit_price(fruit) * _cost_inflation *
               BANANA_PRICE_FACTOR;
    }

    double
    elderberry_farm::sell_elderberry(const size_t index) {
        elderberry const &fruit = _storage[index];
        double const      price = calculate_elderberry_price(fruit);

        remove_fruit(index);

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

        add_fruit(days_to_grow, days_to_spoil, weight);
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

        remove_fruit(index);

        return price;
    }
}
