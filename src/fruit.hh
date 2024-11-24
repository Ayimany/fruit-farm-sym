#ifndef FRUIT_HH
#define FRUIT_HH

#include <string>

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

    [[nodiscard]] auto
    is_ill(
        int    grow,
        double weight
    )
        -> bool;

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

    class fruit {
    public:
        fruit();

        fruit(
            std::string name,
            int         days_until_grown,
            int         days_until_spoilage,
            double      weight
        );

        auto
        tick(
            int days
        )
            -> void;

        [[nodiscard]] auto
        get_name() const
            -> std::string;

        [[nodiscard]] auto
        get_days_to_full_growth() const
            -> int;

        [[nodiscard]] auto
        get_days_until_spoiled() const
            -> int;

        [[nodiscard]] auto
        get_weight() const
            -> double;

        [[nodiscard]] auto
        is_fully_grown() const
            -> bool;

        [[nodiscard]] auto
        is_spoiled() const
            -> bool;

        [[nodiscard]] auto
        is_ill() const
            -> bool;

        [[nodiscard]] auto
        to_string() const
            -> std::string;

    protected:
        std::string _name;
        int         _days_left_to_grow;
        int         _days_left_to_spoil;
        double      _weight;
        bool        _incorrect_care;
    };

    class strawberry : public fruit {
    public:
        strawberry();

        strawberry(
            int    days_until_grown,
            int    days_until_spoilage,
            double weight
        );
    };

    class elderberry : public fruit {
    public:
        elderberry();

        elderberry(
            int    days_until_grown,
            int    days_until_spoilage,
            double weight
        );
    };

    class watermelon : public fruit {
    public:
        watermelon();

        watermelon(
            int    days_until_grown,
            int    days_until_spoilage,
            double weight
        );
    };
}

#endif //FRUIT_HH
