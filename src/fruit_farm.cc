#include "fruit_farm.hh"

#include "constants.hh"

namespace fmk {
    auto
    strawberry_farm::get_fruit_price_factor() const noexcept
        -> double {
        return constants::STRAWBERRY_PRICE_FACTOR - calc::supply_demand_penalty(
                   _fruit_count,
                   _storage.size()
               );
    }

    auto
    elderberry_farm::get_fruit_price_factor() const noexcept
        -> double {
        return constants::ELDERBERRY_PRICE_FACTOR - calc::supply_demand_penalty(
                   _fruit_count,
                   _storage.size()
               );
    }

    auto
    watermelon_farm::get_fruit_price_factor() const noexcept
        -> double {
        return constants::WATERMELON_PRICE_FACTOR - calc::supply_demand_penalty(
                   _fruit_count,
                   _storage.size()
               );
    }
}
