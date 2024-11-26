#ifndef FRUIT_HH
#define FRUIT_HH

#include <string>

#include "fruit_descriptor.hh"

namespace fmk {
    /**
     * Helper class to facilitate template recognition
     */
    struct fruit_base {
    };

    class fruit : public fruit_base {
    public:
        /**
         * Constructs a fruit initialized to all zeroes and ill-care
         */
        explicit
        fruit();

        /**
         * Constructs a fruit object
         * @param name The name of fruit
         * @param days_until_grown The days it will take the fruit to grow
         * @param water_units The amount of water units to give the fruit
         * @param descriptor The provider of a variety of fruit constants
         */
        explicit
        fruit(
            std::string             name,
            int                     days_until_grown,
            double                  water_units,
            fruit_descriptor const &descriptor
        );

        /**
         * Ticks time forward
         * @param days The amount of days
         */
        auto
        tick(
            int days
        )
            -> void;

        /**
         * Returns the name of the fruit
         * @return The name of the fruit
         */
        [[nodiscard]] auto
        get_name() const
            -> std::string;

        /**
         * Returns the days until the fruit is fully grown
         * @return the days until the fruit is fully grown
         */
        [[nodiscard]] auto
        get_days_to_full_growth() const
            -> int;

        /**
         * Returns whether the fruit is fully grown or not
         * @return whether the fruit is fully grown or not
         */
        [[nodiscard]] auto
        is_fully_grown() const
            -> bool;

        /**
         * Returns the days until the fruit is spoiled
         * @return the days until the fruit is spoiled
         */
        [[nodiscard]] auto
        get_days_until_spoiled() const
            -> int;

        /**
         * Returns whether the fruit is spoiled or not
         * @return whether the fruit is spoiled or not
         */
        [[nodiscard]] auto
        is_spoiled() const
            -> bool;

        /**
         * Returns the weight of the fruit
         * @return The weight of the fruit
         */
        [[nodiscard]] auto
        get_weight() const
            -> double;

        /**
         * Returns the fruit's quality factor
         * @return The quality factor
         */
        [[nodiscard]] auto
        get_quality_factor() const
            -> double;

        /**
         * Returns whether the fruit is ill or not
         * @return whether the fruit is ill or not
         */
        [[nodiscard]] auto
        is_ill() const
            -> bool;

        /**
         * Returns this fruit, formatted as a string
         * @return The string-formatted version of the fruit
         */
        [[nodiscard]] auto
        to_string() const
            -> std::string;

    protected:
        /// The name of the fruit
        std::string name_;

        /// The weight of the fruit
        double weight_;

        /// The days left to fully grow
        int days_left_to_grow_;

        /// The days left to spoil
        int days_left_to_spoil_;

        /// A factor that will influence the cost of this fruit
        double quality_factor_;

        /// Determines if this fruit was incorrectly cared for
        bool incorrect_care_;
    };

    class strawberry : public fruit {
    public:
        /**
         * Constructs a strawberry initialized to all zeroes and ill-care
         */
        strawberry();

        /**
         * Constructs a strawberry object
         * @param days_until_grown The days it will take the fruit to grow
         * @param water_units The amount of water units to give the fruit
         */
        strawberry(int days_until_grown, double water_units);
    };

    class elderberry : public fruit {
    public:
        /**
         * Constructs an elderberry initialized to all zeroes and ill-care
         */
        elderberry();

        /**
         * Constructs an elderberry object
         * @param days_until_grown The days it will take the fruit to grow
         * @param water_units The amount of water units to give the fruit
         */
        elderberry(int days_until_grown, double water_units);
    };

    class watermelon : public fruit {
    public:
        /**
         * Constructs a watermelon initialized to all zeroes and ill-care
         */
        watermelon();

        /**
         * Constructs a watermelon object
         * @param days_until_grown The days it will take the fruit to grow
         * @param water_units The amount of water units to give the fruit
         */
        watermelon(int days_until_grown, double water_units);
    };
}

#endif //FRUIT_HH
