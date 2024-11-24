#include "farmer.hh"

namespace fmk {
    farmer::farmer(const double starting_cash)
        : _money { starting_cash }
        , _has_elderberry_farm { false }
        , _has_watermelon_farm { false }
        , _is_best_farmer { false } {
    }

    auto
    farmer::tick(
        const int days
    )
        -> void {
        // Tick all farms
        _strawberry_farm.tick(days);
        _elderberry_farm.tick(days);
        _watermelon_farm.tick(days);
    }

    auto
    farmer::get_money() const
        -> double {
        return _money;
    }

    auto
    farmer::add_money(
        const double amt
    )
        -> void {
        _money += amt;
    }

    auto
    farmer::sub_money(
        const double amt
    )
        -> void {
        _money -= amt;
    }

    auto
    farmer::has_elderberry_farm() const
        -> bool {
        return _has_elderberry_farm;;
    }

    auto
    farmer::has_watermelon_farm() const
        -> bool {
        return _has_watermelon_farm;
    }

    auto
    farmer::get_strawberry_farm()
        -> strawberry_farm & {
        return _strawberry_farm;
    }

    auto
    farmer::enable_elderberry_farm()
        -> void {
        _has_elderberry_farm = true;
    }

    auto
    farmer::get_elderberry_farm()
        -> elderberry_farm & {
        return _elderberry_farm;
    }

    auto
    farmer::enable_watermelon_farm()
        -> void {
        _has_watermelon_farm = true;
    }

    auto
    farmer::get_watermelon_farm()
        -> watermelon_farm & {
        return _watermelon_farm;
    }

    auto
    farmer::get_level() const noexcept
        -> int {
        return 1 + (_has_elderberry_farm
                        ? 1
                        : 0) + (_has_watermelon_farm
                                    ? 1
                                    : 0);
    }

    auto
    farmer::is_best_farmer() const
        -> bool {
        return _is_best_farmer;
    }

    auto
    farmer::become_best_farmer()
        -> void {
        _is_best_farmer = true;
    }
}
