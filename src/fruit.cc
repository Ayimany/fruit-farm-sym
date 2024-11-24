#include "fruit.hh"

#include <cmath>
#include <utility>
#include <stdexcept>

#include "constants.hh"
#include "utility.hh"

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

    [[nodiscard]] auto
    is_ill(
        const int    grow,
        const double weight
    )
        -> bool {
        const auto   growth_real  = static_cast<double>(grow);
        const double biased_water = weight * growth_real;
        const double water_ratio  = biased_water / weight;
        const double weight_ratio = biased_water / weight;

        return water_ratio > ILL_WATER_RATIO || weight_ratio < ILL_WEIGHT_RATIO;
    }

    fruit::fruit()
        : _name("Unknown")
        , _days_left_to_grow(0)
        , _days_left_to_spoil(0)
        , _weight(0.0)
        , _incorrect_care(true) {
    }

    fruit::fruit(
        std::string  name,
        const int    days_until_grown,
        const int    days_until_spoilage,
        const double weight
    )
        : _name(std::move(name))
        , _days_left_to_grow(days_until_grown)
        , _days_left_to_spoil(days_until_spoilage)
        , _weight(weight)
        , _incorrect_care(_days_left_to_spoil <= _days_left_to_grow / 2) {
    }

    auto
    fruit::tick(
        const int days
    )
        -> void {
        if (_days_left_to_grow == 0) {
            _days_left_to_spoil = std::max(_days_left_to_spoil - days, 0);
        }

        _days_left_to_grow = std::max(_days_left_to_grow - days, 0);
    }

    auto
    fruit::get_name() const
        -> std::string {
        return this->_name;
    }

    auto
    fruit::get_days_to_full_growth() const
        -> int {
        return this->_days_left_to_grow;
    }

    auto
    fruit::get_days_until_spoiled() const
        -> int {
        return this->_days_left_to_spoil;
    }

    auto
    fruit::get_weight() const
        -> double {
        return this->_weight;
    }

    auto
    fruit::is_fully_grown() const
        -> bool {
        return this->_days_left_to_grow == 0;
    }

    auto
    fruit::is_spoiled() const
        -> bool {
        return this->_days_left_to_spoil == 0;
    }

    auto
    fruit::is_ill() const
        -> bool {
        return is_spoiled() || _incorrect_care;
    }

    auto
    fruit::to_string() const
        -> std::string {
        std::string base = this->_name + ": ";
        base += util::strfmt("%.2f kg", _weight) + "";

        if (_incorrect_care) {
            base += ". Incorrect care! (Perhaps an ill-mix of water and time)";
        } else if (is_spoiled()) {
            base += ". Spoiled!";
        } else if (is_fully_grown()) {
            base += util::strfmt(". Spoils in: %d days", _days_left_to_spoil);
        } else {
            base += util::strfmt(". Grows in: %d days", _days_left_to_grow);
        }

        return base;
    }

    strawberry::strawberry()
        : strawberry(0, 0, 0) {
    }

    strawberry::strawberry(
        int const    days_until_grown,
        int const    days_until_spoilage,
        double const weight
    )
        : fruit("Strawberry", days_until_grown, days_until_spoilage, weight) {
    }

    elderberry::elderberry()
        : elderberry(0, 0, 0) {
    }

    elderberry::elderberry(
        int const    days_until_grown,
        int const    days_until_spoilage,
        double const weight
    )
        : fruit("Elderberry", days_until_grown, days_until_spoilage, weight) {
    }

    watermelon::watermelon()
        : watermelon(0, 0, 0) {
    }

    watermelon::watermelon(
        int const    days_until_grown,
        int const    days_until_spoilage,
        double const weight
    )
        : fruit("Watermelon", days_until_grown, days_until_spoilage, weight) {
    }
}
