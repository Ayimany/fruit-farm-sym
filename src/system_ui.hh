#ifndef SYSTEM_UI_HH
#define SYSTEM_UI_HH
#include "constants.hh"
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

    template <typename fruit_type_t>
    auto
    request_transfer_ui(
        farmer &                                         the_farmer,
        fruit_farm<fruit_type_t> &                       farm,
        std::pair<request_kind, std::pair<double, int>> &request
    )
        -> void;

    auto
    crop_growth_purchase_ui()
        -> std::pair<int, double>;

    template <typename fruit_type_t>
    auto
    generic_farm_ui(
        std::string const &       name,
        farmer &                  the_farmer,
        fruit_farm<fruit_type_t> &farm
    )
        -> int;

    template <typename fruit_type_t>
    auto
    request_transfer_ui(
        farmer &                                         the_farmer,
        fruit_farm<fruit_type_t> &                       farm,
        std::pair<request_kind, std::pair<double, int>> &request
    )
        -> void {
        const bool has_fruit = farm.get_fruit_count() != 0;

        if (!has_fruit) {
            puts("You have no fruit to offer.");
            return;
        }

        farm.print_fruit();
        divider();

        puts("Which fruits will you offer? Type their number");
        puts("Type 0 to stop offering");

        int index;
        do {
            userprompt();
            std::cin >> index;

            if (index <= 0 || index > farm.get_fruit_count()) {
                puts("Invalid fruit");
                newline();
                continue;
            }

            index--;

            fruit &fruit = farm.get_fruit(index);

            if (fruit.is_spoiled()) {
                puts("You cannot offer this fruit! It is spoiled.");
                newline();
                continue;
            }

            request.second.first -= fruit.get_weight();

            const double cash = farm.sell_fruit(index);
            the_farmer.add_money(cash);

            printf("* Sold for $%.2f\n", cash);
        } while (index != 0 && request.second.second > 0);
    }

    template <typename fruit_type_t>
    auto
    generic_farm_ui(
        std::string const &       name,
        farmer &                  the_farmer,
        fruit_farm<fruit_type_t> &farm
    )
        -> int {
        int choice;
        do {
            divider();

            printf("Welcome to the %s farm\n", name.c_str());
            puts("Please choose an option:");
            puts("0) Exit");
            puts("1) Print farm crops");
            printf("2) Grow a %s\n", name.c_str());
            puts("3) Clear ill crops\n");

            userprompt();
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    divider();
                    farm.print_fruit();
                    break;
                }
                case 2: {
                    const std::pair<int, double> growth_data =
                        crop_growth_purchase_ui();

                    const double water_cost =
                        growth_data.second * constants::COST_PER_WATER_UNIT;

                    const bool will_buy = confirm_purchase_ui(
                        the_farmer,
                        water_cost
                    );

                    if (will_buy) {
                        the_farmer.sub_money(water_cost);
                        farm.grow_fruit(growth_data.first, growth_data.second);
                    }
                    break;
                }
                case 3: {
                    divider();
                    puts("All spoiled or ill-cared for fruit is gone.");
                    farm.remove_ill_fruit();
                    break;
                }
                default: {
                    break;
                }
            }
        } while (choice != 0);

        return choice;
    }
}}

#endif //SYSTEM_UI_HH
