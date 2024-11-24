#ifndef FARMER_HH
#define FARMER_HH
#include "fruit_farm.hh"

namespace fmk {
    class farmer {
    public:
        explicit
        farmer(double starting_cash);

        auto
        tick(
            int days
        )
            -> void;

        [[nodiscard]] auto
        get_money() const
            -> double;

        auto
        add_money(
            double amt
        )
            -> void;

        auto
        sub_money(
            double amt
        )
            -> void;

        auto
        enable_elderberry_farm()
            -> void;

        [[nodiscard]] auto
        has_elderberry_farm() const
            -> bool;

        auto
        enable_watermelon_farm()
            -> void;

        [[nodiscard]] auto
        has_watermelon_farm() const
            -> bool;

        [[nodiscard]] auto
        get_strawberry_farm()
            -> strawberry_farm &;

        [[nodiscard]] auto
        get_elderberry_farm()
            -> elderberry_farm &;

        [[nodiscard]] auto
        get_watermelon_farm()
            -> watermelon_farm &;

        auto
        is_best_farmer() const
            -> bool;

        auto
        become_best_farmer()
            -> void;

    private:
        double _money;
        bool   _has_elderberry_farm;
        bool   _has_watermelon_farm;
        bool   _is_best_farmer;

        strawberry_farm _strawberry_farm;
        elderberry_farm _elderberry_farm;
        watermelon_farm _watermelon_farm;
    };
}

#endif //FARMER_HH
