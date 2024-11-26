#include "farmer.hh"

namespace fmk {
    farmer::farmer(const double starting_cash)
        : money_ { starting_cash }
        , has_elderberry_farm_ { false }
        , has_watermelon_farm_ { false }
        , is_best_farmer_ { false } {
    }

    auto
    farmer::tick(
        const int days
    )
        -> void {
        // Tick all farms
        strawberry_farm_.tick(days);
        elderberry_farm_.tick(days);
        watermelon_farm_.tick(days);
    }

    auto
    farmer::get_money() const
        -> double {
        return money_;
    }

    auto
    farmer::add_money(
        const double amt
    )
        -> void {
        money_ += amt;
    }

    auto
    farmer::sub_money(
        const double amt
    )
        -> void {
        money_ -= amt;
    }

    auto
    farmer::has_elderberry_farm() const
        -> bool {
        return has_elderberry_farm_;;
    }

    auto
    farmer::has_watermelon_farm() const
        -> bool {
        return has_watermelon_farm_;
    }

    auto
    farmer::get_strawberry_farm()
        -> strawberry_farm & {
        return strawberry_farm_;
    }

    auto
    farmer::enable_elderberry_farm()
        -> void {
        has_elderberry_farm_ = true;
    }

    auto
    farmer::get_elderberry_farm()
        -> elderberry_farm & {
        return elderberry_farm_;
    }

    auto
    farmer::enable_watermelon_farm()
        -> void {
        has_watermelon_farm_ = true;
    }

    auto
    farmer::get_watermelon_farm()
        -> watermelon_farm & {
        return watermelon_farm_;
    }

    auto
    farmer::get_level() const noexcept
        -> int {
        return 1 + (has_elderberry_farm_
                        ? 1
                        : 0) + (has_watermelon_farm_
                                    ? 1
                                    : 0);
    }

    auto
    farmer::is_best_farmer() const
        -> bool {
        return is_best_farmer_;
    }

    auto
    farmer::become_best_farmer()
        -> void {
        is_best_farmer_ = true;
    }
}
