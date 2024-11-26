#ifndef FRUIT_MARKET_HH
#define FRUIT_MARKET_HH

#include <array>
#include <iostream>

#include "calculations.hh"
#include "fruit.hh"

namespace fmk {
    /**
     * Represents a fruit farm in which fruit can be grown
     * @tparam fruit_type_t The type of fruit to grow
     */
    template <typename fruit_type_t>
    class fruit_farm {
        static_assert(
            std::is_base_of<fruit_base, fruit_type_t>::value,
            "Fruit farms must be templated with fruit types"
        );

    public:
        /**
         * Constructs a fruit farm object
         */
        fruit_farm()
            : storage_ { }
            , fruit_count_ { 0 } {
        }

        /**
         * Destroys the fruit farm object
         */
        virtual ~fruit_farm() = default;

        /**
         * Ticks time forward
         * @param days The amount of days
         */
        void
        tick(int const days) {
            for (auto &f : storage_) {
                f.tick(days);
            }
        }

        /**
         * Grows a new fruit
         * @param days_to_grow The amount of days it will grow for
         * @param water_units The amount of water that will be given to it
         */
        void
        grow_fruit(const int days_to_grow, double water_units) {
            static_assert(
                std::is_constructible<fruit_type_t, int, double>::value,
                "This fruit type is not constructible with an int and a double"
            );

            fruit_type_t fruit = fruit_type_t { days_to_grow, water_units };

            storage_.at(fruit_count_) = std::move(fruit);
            fruit_count_++;
        }

        /**
         * Sells a fruit
         * @param index The index of the fruit to sell and consequently remove
         * @return The cash generated in the transaction
         */
        double
        sell_fruit(const size_t index) {
            fruit_type_t &fruit = storage_.at(index);
            double const  price = calc::base_fruit_price(fruit);

            remove_fruit(index);

            return price * get_fruit_price_factor();
        }

        /**
         * Returns a fruit from the fruit storage
         * @param index The index of the fruit
         * @return The fruit
         */
        [[nodiscard]] auto
        get_fruit(
            size_t index
        )
            -> fruit_type_t & {
            return storage_.at(index);
        }

        /**
         * Removes all ill-cared-for or spoiled fruit
         */
        void
        remove_ill_fruit() {
            std::array<fruit_type_t, 128> fruits;
            int                           count = 0;

            for (auto &fruit : storage_) {
                if (!fruit.is_ill()) {
                    fruits.at(count++) = std::move(fruit);
                }
            }

            fruit_count_ = count;
            storage_     = fruits;
        }

        /**
         * Checks whether more fruit can be added
         * @return If more fruit can be added
         */
        bool
        can_add_more_fruit() const {
            return fruit_count_ < storage_.size();
        }

        /**
         * Returns the amount of fruit in the farm
         * @return The amount of fruit in the farm
         */
        size_t
        get_fruit_count() const {
            return fruit_count_;
        }

        /**
         * Prints all fruit currently inhabiting this farm
         */
        void
        print_fruit() const {
            printf("There are %lu fruits\n\n", fruit_count_);
            for (size_t i = 0; i < fruit_count_; ++i) {
                std::cout << (i + 1) << ") " << storage_.at(i).to_string() <<
                    "\n";
            }
        }

    protected:
        /// The fruit storage
        std::array<fruit_type_t, 128> storage_;

        /// Used to keep track of the valid fruits in storage
        size_t fruit_count_;

        /**
         * Returns a specific price multiplier per fruit
         * @return The price factor of this fruit
         */
        [[nodiscard]] virtual auto
        get_fruit_price_factor() const noexcept
            -> double = 0;

    private:
        /**
         * Removes a fruit from the fruit storage
         * @param index The fruit to remove
         */
        auto
        remove_fruit(
            const size_t index
        )
            -> void {
            if (index == fruit_count_) {
                fruit_count_--;
                return;
            }

            for (size_t i = index; i < fruit_count_; ++i) {
                storage_[i] = std::move(storage_[i + 1]);
            }

            fruit_count_--;
        }
    };

    class strawberry_farm final : public fruit_farm<strawberry> {
    protected:
        /**
         * Returns the price factor for a strawberry
         * @return the price factor for a strawberry
         */
        [[nodiscard]] auto
        get_fruit_price_factor() const noexcept
            -> double override;
    };

    class elderberry_farm final : public fruit_farm<elderberry> {
    protected:
        /**
         * Returns the price factor for an elderberry
         * @return the price factor for an elderberry
         */
        [[nodiscard]] auto
        get_fruit_price_factor() const noexcept
            -> double override;
    };

    class watermelon_farm final : public fruit_farm<watermelon> {
    protected:
        /**
         * Returns the price factor for a watermelon
         * @return the price factor for a watermelon
         */
        [[nodiscard]] auto
        get_fruit_price_factor() const noexcept
            -> double override;
    };
}

#endif //FRUIT_MARKET_HH
