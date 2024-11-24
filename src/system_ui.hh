#ifndef SYSTEM_UI_HH
#define SYSTEM_UI_HH
#include "farmer.hh"

namespace fmk { namespace ui {
    auto
    newline()
        -> void;

    auto
    userprompt()
        -> void;

    auto
    divider()
        -> void;

    auto
    print_welcome()
        -> void;

    auto
    print_farmer_data(
        farmer &the_farmer
    )
        -> void;

    auto
    ff_ui(
        farmer &the_farmer
    )
        -> void;

    auto
    menu_ui(
        const farmer &the_farmer
    )
        -> int;

    auto
    confirm_purchase_ui(
        const farmer &the_farmer,
        double        amt
    )
        -> bool;

    auto
    shop_ui(
        const farmer &farmer
    )
        -> void;

    auto
    requests_ui(
        const farmer &farmer
    )
        -> void;

    auto
    crop_growth_purchase_ui()
        -> std::pair<double, int>;

    auto
    generic_farm_ui(
        std::string const &name
    )
        -> int;

    auto
    strawberry_farm_ui(
        farmer &the_farmer
    )
        -> void;

    auto
    elderberry_farm_ui(
        farmer &the_farmer
    )
        -> void;

    auto
    watermelon_farm_ui(
        farmer &the_farmer
    )
        -> void;
}}

#endif //SYSTEM_UI_HH
