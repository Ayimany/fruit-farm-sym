#include "fruit.hh"

#include <cmath>
#include <stdexcept>
#include <utility>

#include "calculations.hh"
#include "utility.hh"

namespace fmk {
    fruit::fruit()
        : name_ { "Unknown" }
        , weight_ { 0.0 }
        , days_left_to_grow_ { 0 }
        , days_left_to_spoil_ { 0 }
        , quality_factor_ { 0 }
        , incorrect_care_ { true } {
    }

    fruit::fruit(
        std::string             name,
        const int               days_until_grown,
        const double            water_units,
        fruit_descriptor const &descriptor
    )
        : name_ { std::move(name) }
        , weight_ {
            calc::fruit_weight(
                days_until_grown,
                water_units,
                descriptor.get_weight_factor(),
                descriptor.get_water_factor()
            )
        }
        , days_left_to_grow_ { days_until_grown }
        , days_left_to_spoil_ {
            calc::days_to_spoil(
                days_left_to_grow_,
                weight_,
                descriptor.get_spoiling_factor()
            )
        }
        , quality_factor_ { calc::fruit_quality(days_until_grown, water_units) }
        , incorrect_care_ {
            calc::ill_status(
                days_until_grown,
                water_units,
                descriptor.get_ill_ratio_bounds()
            )
        } {
    }

    auto
    fruit::tick(
        const int days
    )
        -> void {
        int residue = days;

        if (days_left_to_grow_ > 0) {
            residue            = std::max(days - days_left_to_grow_, 0);
            days_left_to_grow_ = std::max(days_left_to_grow_ - days, 0);
        }

        if (days_left_to_grow_ == 0 && residue > 0) {
            days_left_to_spoil_ = std::max(days_left_to_spoil_ - residue, 0);
        }
    }

    auto
    fruit::get_name() const
        -> std::string {
        return name_;
    }

    auto
    fruit::get_days_to_full_growth() const
        -> int {
        return days_left_to_grow_;
    }

    auto
    fruit::is_fully_grown() const
        -> bool {
        return days_left_to_grow_ == 0;
    }

    auto
    fruit::get_days_until_spoiled() const
        -> int {
        return days_left_to_spoil_;
    }

    auto
    fruit::is_spoiled() const
        -> bool {
        return days_left_to_spoil_ == 0;
    }

    auto
    fruit::get_weight() const
        -> double {
        return weight_;
    }

    auto
    fruit::get_quality_factor() const
        -> double {
        return quality_factor_;
    }

    auto
    fruit::is_ill() const
        -> bool {
        return is_spoiled() || incorrect_care_;
    }

    auto
    fruit::to_string() const
        -> std::string {
        std::string base = this->name_ + ": ";
        base += util::strfmt("%.2f kg", weight_) + "";

        if (incorrect_care_) {
            base += ". Incorrect care! (Perhaps an ill-mix of water and time)";
        } else if (is_spoiled()) {
            base += ". Spoiled!";
        } else if (is_fully_grown()) {
            base += util::strfmt(". Spoils in: %d days", days_left_to_spoil_);
        } else {
            base += util::strfmt(". Grows in: %d days", days_left_to_grow_);
        }

        return base;
    }

    strawberry::strawberry()
        : strawberry { 0, 0 } {
    }

    strawberry::strawberry(const int days_until_grown, const double water_units)
        : fruit {
            "Strawberry",
            days_until_grown,
            water_units,
            strawberry_descriptor { }
        } {
    }

    elderberry::elderberry()
        : elderberry { 0, 0 } {
    }

    elderberry::elderberry(const int days_until_grown, const double water_units)
        : fruit {
            "Elderberry",
            days_until_grown,
            water_units,
            elderberry_descriptor { }
        } {
    }

    watermelon::watermelon()
        : watermelon { 0, 0 } {
    }

    watermelon::watermelon(const int days_until_grown, const double water_units)
        : fruit {
            "Watermelon",
            days_until_grown,
            water_units,
            watermelon_descriptor { }
        } {
    }
}
