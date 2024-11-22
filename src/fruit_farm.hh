#ifndef FRUIT_MARKET_HH
#define FRUIT_MARKET_HH

#include <iostream>

#include "fruit.hh"
#include "tight_dynamic_array.hh"

namespace fmk {
    [[nodiscard]] auto
    calculate_fruit_weight(
        double water_units,
        int    days_to_grow,
        double water_factor
    ) noexcept
        -> double;

    [[nodiscard]] auto
    calculate_spoiling_penalty(
        double weight
    ) noexcept
        -> int;

    [[nodiscard]] auto
    calculate_days_to_spoil(
        int    days_to_grow,
        double weight,
        double spoilage_factor
    ) noexcept
        -> int;

    template <typename fruit_type_t>
    [[nodiscard]] auto
    calculate_generic_fruit_price(
        fruit_type_t const &fruit
    ) noexcept
        -> double {
        if (fruit.is_spoiled()) {
            return 0.0;
        }

        return (fruit.get_weight()) / (fruit.get_days_to_full_growth() + 1);
    }

    template <typename fruit_type_t>
    class fruit_farm {
    public:
        fruit_farm()
            : _cost_inflation(1.0)
            , _fruit_count(0)
            , _storage() {
        }

        void
        tick() {
            for (auto const &f : _storage) {
                f.tick();
            }
        }

        void
        print_fruit() const {
            for (fruit_type_t const &fruit : _storage) {
                std::cout << fruit.to_string() << "\n";
            }
        }

    protected:
        double                            _cost_inflation;
        int                               _fruit_count;
        tight_dynamic_array<fruit_type_t> _storage;
    };

    class strawberry_farm : public fruit_farm<strawberry> {
    public:
        strawberry_farm();

        void
        grow_strawberry(double water_units, int days_to_grow);

        double
        calculate_strawberry_price(strawberry const &fruit) const;

        double
        sell_strawberry(size_t index);
    };

    class banana_farm : public fruit_farm<banana> {
    public:
        banana_farm();

        void
        grow_banana(double water_units, int days_to_grow);

        double
        calculate_banana_price(banana const &fruit) const;

        double
        sell_banana(size_t index);
    };

    class watermelon_farm : public fruit_farm<watermelon> {
    public:
        watermelon_farm();

        double
        calculate_watermelon_price(watermelon const &fruit) const;

        void
        grow_watermelon(double water_units, int days_to_grow);

        double
        sell_watermelon(size_t index);
    };
}

#endif //FRUIT_MARKET_HH
