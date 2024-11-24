#ifndef SYSTEM_UI_HH
#define SYSTEM_UI_HH
#include "constants.hh"
#include "farmer.hh"
#include "request_generator.hh"

namespace fmk {
    class request_generator;
}

namespace fmk { namespace ui {
    /**
     * Shorhthand to print a newline
     */
    auto
    newline()
        -> void;

    /**
     * Shorthand to print a pretty user prompt
     */
    auto
    userprompt()
        -> void;

    /**
     * Shorthand to print a pretty divider
     */
    auto
    divider()
        -> void;

    /**
     * Welcomes the farmer
     */
    auto
    print_welcome()
        -> void;

    /**
     * Prints a farmer's information
     * @param the_farmer The farmer to print the info of
     */
    auto
    print_farmer_data(
        const farmer &the_farmer
    )
        -> void;

    /**
     * A UI to fast-forward time
     * @param the_farmer The farmer
     * @param generator The request generator
     */
    auto
    print_fast_forward_ui(
        farmer &           the_farmer,
        request_generator &generator
    )
        -> void;

    /**
     * Prints the main menu
     * @param the_farmer The farmer
     * @return The user's choice
     */
    auto
    print_menu_ui(
        const farmer &the_farmer
    )
        -> int;

    /**
     * Asks the user if they would like to confirm a purchase
     * @param the_farmer The farmer
     * @param amt The amount of money
     * @return Whether the user has enough money and accepts
     */
    auto
    print_purchase_confirmation_ui(
        const farmer &the_farmer,
        double        amt
    )
        -> bool;

    /**
     * Prints the shop UI
     * @param the_farmer The farmer
     */
    auto
    print_shop_ui(
        farmer &the_farmer
    )
        -> void;

    /**
     * Displays the information of a request
     * @param request The request
     */
    auto
    print_request_display_element(
        const std::pair<request_kind, std::pair<double, int>> &request
    )
        -> void;

    /**
     * Prints the request management UI
     * @param the_farmer The farmer
     * @param generator The request generator
     */
    auto
    print_requests_ui(
        farmer &           the_farmer,
        request_generator &generator
    )
        -> void;

    /**
     * Prints the UI to choose a request
     * @param the_farmer The farmer
     * @param generator The request generator
     */
    auto
    print_request_fetching_ui(
        farmer &           the_farmer,
        request_generator &generator
    )
        -> void;

    /**
     * Checks if this request is still valid
     * @param request The request
     * @return Whether the request is valid
     */
    auto
    print_request_validation_note_element(
        const std::pair<request_kind, std::pair<double, int>> &request
    )
        -> bool;

    /**
     * Intermediate UI to where to user can fill a request
     * @param the_farmer The farmer
     * @param request The request
     */
    auto
    print_request_fulfilment_ui(
        farmer &                                         the_farmer,
        std::pair<request_kind, std::pair<double, int>> &request
    )
        -> void;

    /**
     * UI where to user can fill a request
     * @param the_farmer The farmer
     * @param farm The farm
     * @param request The request
     */
    template <typename fruit_type_t>
    auto
    print_request_transfer_ui(
        farmer &                                         the_farmer,
        fruit_farm<fruit_type_t> &                       farm,
        std::pair<request_kind, std::pair<double, int>> &request
    )
        -> void;

    /**
     * UI for the user to enter days and water units for a crop
     * @return The days and water units the user chose
     */
    auto
    print_crop_growth_params_ui()
        -> std::pair<int, double>;

    /**
     * Prints a farm management UI
     * @tparam fruit_type_t The type of fruit
     * @param name The name of the crop
     * @param the_farmer The farmer
     * @param farm The farm
     */
    template <typename fruit_type_t>
    auto
    print_generic_farm_ui(
        std::string const &       name,
        farmer &                  the_farmer,
        fruit_farm<fruit_type_t> &farm
    )
        -> void;

    // IMPLEMENTATIONS OF TEMPLATED UIs AHEAD //

    template <typename fruit_type_t>
    auto
    print_request_transfer_ui(
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
    print_generic_farm_ui(
        std::string const &       name,
        farmer &                  the_farmer,
        fruit_farm<fruit_type_t> &farm
    )
        -> void {
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
                        print_crop_growth_params_ui();

                    const double water_cost =
                        growth_data.second * constants::COST_PER_WATER_UNIT;

                    const bool will_buy = print_purchase_confirmation_ui(
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
    }
}}

#endif //SYSTEM_UI_HH
