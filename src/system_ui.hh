#ifndef SYSTEM_UI_HH
#define SYSTEM_UI_HH
#include "farmer.hh"
#include "request_generator.hh"

namespace fmk {
    class request_generator;
}

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
        const farmer &the_farmer
    )
        -> void;

    auto
    ff_ui(
        farmer &           the_farmer,
        request_generator &generator
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
        farmer &the_farmer
    )
        -> void;

    auto
    display_request(
        const std::pair<request_kind, std::pair<double, int>> &request
    )
        -> void;

    auto
    requests_ui(
        farmer &           the_farmer,
        request_generator &generator
    )
        -> void;

    auto
    request_fetching_ui(
        farmer &           the_farmer,
        request_generator &generator
    )
        -> void;

    auto
    request_validation_note(
        const std::pair<request_kind, std::pair<double, int>> &request
    )
        -> bool;

    auto
    request_fulfilment_ui(
        farmer &                                         the_farmer,
        std::pair<request_kind, std::pair<double, int>> &request
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
