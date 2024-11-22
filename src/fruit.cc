#include <utility>

#include "fruit.hh"

namespace fmk {
    fruit::fruit(
        std::string  name,
        const int    days_until_grown,
        const int    days_until_spoilage,
        const double weight
    )
        : _name(std::move(name))
        , _days_left_to_grow(days_until_grown)
        , _days_left_to_spoil(days_until_spoilage)
        , _weight(weight) {
    }

    void
    fruit::tick() {
        if (this->_days_left_to_grow > 0) {
            this->_days_left_to_grow--;
        }

        if (this->_days_left_to_spoil > 0) {
            this->_days_left_to_spoil--;
        }
    }

    std::string
    fruit::get_name() const {
        return this->_name;
    }

    int
    fruit::get_days_to_full_growth() const {
        return this->_days_left_to_grow;
    }

    int
    fruit::get_days_until_spoiled() const {
        return this->_days_left_to_spoil;
    }

    double
    fruit::get_weight() const {
        return this->_weight;
    }

    bool
    fruit::is_fully_grown() const {
        return this->_days_left_to_grow == 0;
    }

    bool
    fruit::is_spoiled() const {
        return this->_days_left_to_spoil == 0;
    }

    std::string
    fruit::to_string() const {
        return this->_name + ": " + " [Weight] " + std::to_string(this->_weight)
               + " [Grown?] " + std::to_string(this->is_fully_grown()) +
               " [Spoiled?] " + std::to_string(this->is_spoiled());
    }

    strawberry::strawberry(
        int const    days_until_grown,
        int const    days_until_spoilage,
        double const weight
    )
        : fruit("Strawberry", days_until_grown, days_until_spoilage, weight) {
    }

    banana::banana(
        int const    days_until_grown,
        int const    days_until_spoilage,
        double const weight
    )
        : fruit("Banana", days_until_grown, days_until_spoilage, weight) {
    }

    watermelon::watermelon(
        int const    days_until_grown,
        int const    days_until_spoilage,
        double const weight
    )
        : fruit("Watermelon", days_until_grown, days_until_spoilage, weight) {
    }
}
