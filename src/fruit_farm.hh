#ifndef FRUIT_MARKET_HH
#define FRUIT_MARKET_HH

#include <array>
#include <iostream>

#include "calculations.hh"
#include "fruit.hh"

namespace fmk {
    template <typename fruit_type_t>
    class fruit_farm {
        static_assert(
            std::is_base_of<fruit_base, fruit_type_t>::value,
            "Fruit farms must be templated with fruit types"
        );

    public:
        fruit_farm()
            : _storage()
            , _fruit_count(0) {
        }

        virtual ~fruit_farm() = default;

        void
        tick(int const days) {
            for (auto &f : _storage) {
                f.tick(days);
            }
        }

        void
        grow_fruit(const int days_to_grow, double water_units) {
            static_assert(
                std::is_constructible<fruit_type_t, int, double>::value,
                "This fruit type is not constructible with an int and a double"
            );

            fruit_type_t fruit = fruit_type_t { days_to_grow, water_units };

            _storage.at(_fruit_count) = std::move(fruit);
            _fruit_count++;
            std::cout << "!";
        }

        double
        sell_fruit(const size_t index) {
            fruit_type_t &fruit = _storage.at(index);
            double const  price = calc::base_fruit_price(fruit);

            remove_fruit(index);

            return price * get_fruit_price_factor();
        }

        [[nodiscard]] auto
        get_fruit(
            size_t index
        )
            -> fruit_type_t & {
            return _storage.at(index);
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

        bool
        can_add_more_fruit() const {
            return _fruit_count < _storage.size();
        }

        size_t
        get_fruit_count() const {
            return _fruit_count;
        }

        void
        print_fruit() const {
            printf("There are %lu fruits\n\n", _fruit_count);
            for (size_t i = 0; i < _fruit_count; ++i) {
                std::cout << (i + 1) << ") " << _storage.at(i).to_string() <<
                    "\n";
            }
        }

    protected:
        std::array<fruit_type_t, 128> _storage;
        size_t                        _fruit_count;

        [[nodiscard]] virtual auto
        get_fruit_price_factor() const noexcept
            -> double = 0;

    private:
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
    };

    class strawberry_farm final : public fruit_farm<strawberry> {
    protected:
        [[nodiscard]] auto
        get_fruit_price_factor() const noexcept
            -> double override;
    };

    class elderberry_farm final : public fruit_farm<elderberry> {
    protected:
        [[nodiscard]] auto
        get_fruit_price_factor() const noexcept
            -> double override;
    };

    class watermelon_farm final : public fruit_farm<watermelon> {
    protected:
        [[nodiscard]] auto
        get_fruit_price_factor() const noexcept
            -> double override;
    };
}

#endif //FRUIT_MARKET_HH
