#ifndef FARMER_HH
#define FARMER_HH
#include "fruit_farm.hh"

namespace fmk {
    class farmer {
    public:
        /**
         * Constructs a farmer
         * @param starting_cash The amount of money they wull start with
         */
        explicit
        farmer(double starting_cash);

        /**
         * Causes the farmer's farms to tick time forwards
         * @param days The amount of days
         */
        auto
        tick(
            int days
        )
            -> void;

        /**
         * Returns the farmer's money
         * @return The farmer's money
         */
        [[nodiscard]] auto
        get_money() const
            -> double;

        /**
         * Adds money to the farmer's balance
         * @param amt The amount to add
         */
        auto
        add_money(
            double amt
        )
            -> void;

        /**
         * Subtracts money from the farmer's balance
         * @param amt The amount to remove
         */
        auto
        sub_money(
            double amt
        )
            -> void;

        /**
         * Allows the farmer to interface with their elderberry farm
         */
        auto
        enable_elderberry_farm()
            -> void;

        /**
         * Checks if the farmer can access their elderberry farm or not
         * @return If the farmer can access the farm
         */
        [[nodiscard]] auto
        has_elderberry_farm() const
            -> bool;

        /**
         * Allows the farmer to interface with their watermelon farm
         */
        auto
        enable_watermelon_farm()
            -> void;

        /**
         * Checks if the farmer can access their watermelon farm or not
         * @return If the farmer can access the farm
         */
        [[nodiscard]] auto
        has_watermelon_farm() const
            -> bool;

        /**
         * Returns a reference to the farmer's strawberry farm
         * @return The farm
         */
        [[nodiscard]] auto
        get_strawberry_farm()
            -> strawberry_farm &;

        /**
         * Returns a reference to the farmer's elderberry farm
         * @return The farm
         */
        [[nodiscard]] auto
        get_elderberry_farm()
            -> elderberry_farm &;

        /**
         * Returns a reference to the farmer's watermelon farm
         * @return The farm
         */
        [[nodiscard]] auto
        get_watermelon_farm()
            -> watermelon_farm &;

        [[nodiscard]] auto
        get_level() const noexcept
            -> int;

        /**
         * Checks if this farmer has the `best farmer` title
         * @return
         */
        auto
        is_best_farmer() const
            -> bool;

        /**
         * Sets this farmer's status to "Best farmer"
         */
        auto
        become_best_farmer()
            -> void;

    private:
        /// The farmer's balance
        double money_;

        /// Determines if the farmer has an elderberry farm
        bool has_elderberry_farm_;

        /// Determines if the farmer has a watermelon farm
        bool has_watermelon_farm_;

        /// Determines if the farmer is the best farmer
        bool is_best_farmer_;

        /// The farmer's strawberry farm
        strawberry_farm strawberry_farm_;

        /// The farmer's elderberry farm
        elderberry_farm elderberry_farm_;

        /// The farmer's watermelon farm
        watermelon_farm watermelon_farm_;
    };
}

#endif //FARMER_HH
