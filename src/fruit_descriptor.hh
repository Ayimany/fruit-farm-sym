#ifndef FRUIT_DESCRIPTOR_HH
#define FRUIT_DESCRIPTOR_HH
#include <utility>

namespace fmk {
    class fruit_descriptor {
    public:
        virtual ~fruit_descriptor();

        /**
         * Returns a factor that will influence the weight of this fruit
         *
         * A higher factor will result in more weight
         *
         * @return The weight factor
         */
        [[nodiscard]] virtual auto
        get_weight_factor() const noexcept
            -> double = 0;

        /**
         * Returns a factor that will influence the fruit's water consumption
         *
         * A higher factor will result in more consumption, thus less weight
         *
         * @return The water factor
         */
        [[nodiscard]] virtual auto
        get_water_factor() const noexcept
            -> double = 0;

        /**
         * Returns a factor that will influence the spoiling time of this fruit
         *
         * A higher factor will result in more spoiling time
         *
         * @return The spoiling factor
         */
        [[nodiscard]] virtual auto
        get_spoiling_factor() const noexcept
            -> double = 0;

        /**
         * Returns the water to days ratios (lower and upper bounds)
         * for a fruit to be ill.
         *
         * Ill-care when:<br>
         * @code R = water / days @endcode <br>
         * @code R < lower_bound || R > upper_bound @endcode
         *
         * @return The ill ratio bounds
         */
        [[nodiscard]] virtual auto
        get_ill_ratio_bounds() const noexcept
            -> std::pair<double, double> = 0;
    };

    class strawberry_descriptor final : public fruit_descriptor {
    public:
        /**
         * Returns the strawberry's weight factor
         * @return The weight factor
         */
        [[nodiscard]] auto
        get_weight_factor() const noexcept
            -> double override;

        /**
         * Returns the strawberry's water factor
         * @return The water factor
         */
        [[nodiscard]] auto
        get_water_factor() const noexcept
            -> double override;

        /**
         * Returns the strawberry's spoiling factor
         * @return The spoiling factor
         */
        [[nodiscard]] auto
        get_spoiling_factor() const noexcept
            -> double override;

        /**
         * Returns the strawberry's ill bounds
         * @return The ill ratio bounds
         */
        [[nodiscard]] auto
        get_ill_ratio_bounds() const noexcept
            -> std::pair<double, double> override;
    };

    class elderberry_descriptor final : public fruit_descriptor {
    public:
        /**
         * Returns the elderberry's weight factor
         * @return The weight factor
         */
        [[nodiscard]] auto
        get_weight_factor() const noexcept
            -> double override;

        /**
         * Returns the elderberry's water factor
         * @return The water factor
         */
        [[nodiscard]] auto
        get_water_factor() const noexcept
            -> double override;

        /**
         * Returns the elderberry's spoiling factor
         * @return The spoiling factor
         */
        [[nodiscard]] auto
        get_spoiling_factor() const noexcept
            -> double override;

        /**
         * Returns the elderberry's ill bounds
         * @return The ill ratio bounds
         */
        [[nodiscard]] auto
        get_ill_ratio_bounds() const noexcept
            -> std::pair<double, double> override;
    };

    class watermelon_descriptor final : public fruit_descriptor {
    public:
        /**
         * Returns the watermelon's weight factor
         * @return The weight factor
         */
        [[nodiscard]] auto
        get_weight_factor() const noexcept
            -> double override;

        /**
         * Returns the watermelon's water factor
         * @return The water factor
         */
        [[nodiscard]] auto
        get_water_factor() const noexcept
            -> double override;

        /**
         * Returns the watermelon's spoiling factor
         * @return The spoiling factor
         */
        [[nodiscard]] auto
        get_spoiling_factor() const noexcept
            -> double override;

        /**
         * Returns the watermelon's ill bounds
         * @return The ill ratio bounds
         */
        [[nodiscard]] auto
        get_ill_ratio_bounds() const noexcept
            -> std::pair<double, double> override;
    };
}

#endif //FRUIT_DESCRIPTOR_HH
