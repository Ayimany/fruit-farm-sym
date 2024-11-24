#ifndef FRUIT_MARKET_HH
#define FRUIT_MARKET_HH

#include <iostream>
#include <array>

#include "fruit.hh"

namespace fmk {
    template <typename fruit_type_t>
    class fruit_farm {
    public:
        fruit_farm()
            : _cost_inflation(1.0)
            , _storage()
            , _fruit_count(0) {
        }

        void
        tick(int const days) {
            for (auto &f : _storage) {
                f.tick(days);
            }
        }

        void
        print_fruit() const {
            printf("There are %lu fruits\n", _fruit_count);
            for (size_t i = 0; i < _fruit_count; ++i) {
                std::cout << _storage.at(i).to_string() << "\n";
            }
        }

        void
        add_fruit(
            const int    days_to_grow,
            const int    days_to_spoil,
            const double weight
        ) {
            fruit_type_t fruit = fruit_type_t {
                days_to_grow,
                days_to_spoil,
                weight
            };

            _storage.at(_fruit_count) = std::move(fruit);
            _fruit_count++;
        }

        auto
        remove_fruit(
            const size_t index
        )
            -> void {
            if (index == _fruit_count) {
                _fruit_count--;
                return;
            }

            for (size_t i = index; i < _fruit_count; ++i) {
                _storage[i] = std::move(_storage[i + 1]);
            }

            _fruit_count--;
        }

        bool
        can_add_more_fruit() const {
            return _fruit_count < _storage.size();
        }

        void
        remove_ill_fruit() {
            std::array<fruit_type_t, 128> fruits;
            int                           count = 0;

            for (auto &fruit : _storage) {
                if (!fruit.is_ill()) {
                    fruits.at(count++) = std::move(fruit);
                }
            }

            _fruit_count = count;
            _storage     = fruits;
        }

        size_t
        get_fruit_count() const {
            return _fruit_count;
        }

    protected:
        double                        _cost_inflation;
        std::array<fruit_type_t, 128> _storage;
        size_t                        _fruit_count;
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

    class elderberry_farm : public fruit_farm<elderberry> {
    public:
        elderberry_farm();

        void
        grow_elderberry(double water_units, int days_to_grow);

        double
        calculate_elderberry_price(elderberry const &fruit) const;

        double
        sell_elderberry(size_t index);
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
