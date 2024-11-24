#include "fruit_descriptor.hh"

#include "constants.hh"
#include "fruit.hh"

namespace fmk {
    fruit_descriptor::~fruit_descriptor() = default;

    auto
    strawberry_descriptor::get_weight_factor() const noexcept
        -> double {
        return constants::STRAWBERRY_WEIGHT_FACTOR;
    }

    auto
    strawberry_descriptor::get_water_factor() const noexcept
        -> double {
        return constants::STRAWBERRY_WATER_FACTOR;
    }

    auto
    strawberry_descriptor::get_spoiling_factor() const noexcept
        -> double {
        return constants::STRAWBERRY_SPOILING_FACTOR;
    }

    auto
    strawberry_descriptor::get_ill_ratio_bounds() const noexcept
        -> std::pair<double, double> {
        return std::make_pair(
            constants::STRAWBERRY_ILL_LOWER_BOUND,
            constants::STRAWBERRY_ILL_UPPER_BOUND
        );
    }

    auto
    elderberry_descriptor::get_weight_factor() const noexcept
        -> double {
        return constants::ELDERBERRY_WEIGHT_FACTOR;
    }

    auto
    elderberry_descriptor::get_water_factor() const noexcept
        -> double {
        return constants::ELDERBERRY_WATER_FACTOR;
    }

    auto
    elderberry_descriptor::get_spoiling_factor() const noexcept
        -> double {
        return constants::ELDERBERRY_SPOILING_FACTOR;
    }

    auto
    elderberry_descriptor::get_ill_ratio_bounds() const noexcept
        -> std::pair<double, double> {
        return std::make_pair(
            constants::ELDERBERRY_ILL_LOWER_BOUND,
            constants::ELDERBERRY_ILL_UPPER_BOUND
        );
    }

    auto
    watermelon_descriptor::get_weight_factor() const noexcept
        -> double {
        return constants::WATERMELON_WEIGHT_FACTOR;
    }

    auto
    watermelon_descriptor::get_water_factor() const noexcept
        -> double {
        return constants::WATERMELON_WATER_FACTOR;
    }

    auto
    watermelon_descriptor::get_spoiling_factor() const noexcept
        -> double {
        return constants::WATERMELON_SPOILING_FACTOR;
    }

    auto
    watermelon_descriptor::get_ill_ratio_bounds() const noexcept
        -> std::pair<double, double> {
        return std::make_pair(
            constants::WATERMELON_ILL_LOWER_BOUND,
            constants::WATERMELON_ILL_UPPER_BOUND
        );
    }
}
