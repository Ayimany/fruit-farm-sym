#include "fruit.hh"

#include <cmath>
#include <stdexcept>
#include <utility>

#include "calculations.hh"
#include "utility.hh"

namespace fmk {
    fruit::fruit()
        : _name("Unknown")
        , _weight(0.0)
        , _days_left_to_grow(0)
        , _days_left_to_spoil(0)
        , _quality_factor(0)
        , _incorrect_care(true) {
    }

    fruit::fruit(
        std::string             name,
        const int               days_until_grown,
        const double            water_units,
        fruit_descriptor const &descriptor
    )
        : _name(std::move(name))
        , _weight(
            calc::fruit_weight(
                days_until_grown,
                water_units,
                descriptor.get_weight_factor(),
                descriptor.get_water_factor()
            )
        )
        , _days_left_to_grow(days_until_grown)
        , _days_left_to_spoil(
            calc::days_to_spoil(
                _days_left_to_grow,
                _weight,
                descriptor.get_spoiling_factor()
            )
        )
        , _quality_factor(calc::fruit_quality(days_until_grown, water_units))
        , _incorrect_care(
            calc::ill_status(
                days_until_grown,
                water_units,
                descriptor.get_ill_ratio_bounds()
            )
        ) {
    }

    auto
    fruit::tick(
        const int days
    )
        -> void {
        int residue = days;

        if (_days_left_to_grow > 0) {
            residue            = std::max(days - _days_left_to_grow, 0);
            _days_left_to_grow = std::max(_days_left_to_grow - days, 0);
        }

        if (_days_left_to_grow == 0 && residue > 0) {
            _days_left_to_spoil = std::max(_days_left_to_spoil - residue, 0);
        }
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
    fruit::is_fully_grown() const
        -> bool {
        return this->_days_left_to_grow == 0;
    }

    auto
    fruit::get_days_until_spoiled() const
        -> int {
        return this->_days_left_to_spoil;
    }

    auto
    fruit::is_spoiled() const
        -> bool {
        return this->_days_left_to_spoil == 0;
    }

    auto
    fruit::get_weight() const
        -> double {
        return this->_weight;
    }

    auto
    fruit::get_quality_factor() const
        -> double {
        return _quality_factor;
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
        : strawberry(0, 0) {
    }

    strawberry::strawberry(const int days_until_grown, const double water_units)
        : fruit(
            "Strawberry",
            days_until_grown,
            water_units,
            strawberry_descriptor { }
        ) {
    }

    elderberry::elderberry()
        : elderberry(0, 0) {
    }

    elderberry::elderberry(const int days_until_grown, const double water_units)
        : fruit(
            "Elderberry",
            days_until_grown,
            water_units,
            elderberry_descriptor { }
        ) {
    }

    watermelon::watermelon()
        : watermelon(0, 0) {
    }

    watermelon::watermelon(const int days_until_grown, const double water_units)
        : fruit(
            "Watermelon",
            days_until_grown,
            water_units,
            watermelon_descriptor { }
        ) {
    }
}
