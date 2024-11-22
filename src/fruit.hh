#ifndef FRUIT_HH
#define FRUIT_HH

#include <string>

namespace fmk {
    class fruit {
    public:
        fruit(
            std::string name,
            int         days_until_grown,
            int         days_until_spoilage,
            double      weight
        );

        void
        tick();

        std::string
        get_name() const;

        int
        get_days_to_full_growth() const;

        int
        get_days_until_spoiled() const;

        double
        get_weight() const;

        bool
        is_fully_grown() const;

        bool
        is_spoiled() const;

        std::string
        to_string() const;

    private:
        std::string _name;
        int         _days_left_to_grow;
        int         _days_left_to_spoil;
        double      _weight;
    };

    class strawberry : public fruit {
    public:
        strawberry(
            int    days_until_grown,
            int    days_until_spoilage,
            double weight
        );
    };

    class banana : public fruit {
    public:
        banana(int days_until_grown, int days_until_spoilage, double weight);
    };

    class watermelon : public fruit {
    public:
        watermelon(
            int    days_until_grown,
            int    days_until_spoilage,
            double weight
        );
    };
}

#endif //FRUIT_HH
