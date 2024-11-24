#include "system_ui.hh"

#include <iostream>

#include "constants.hh"
#include "utility.hh"

namespace fmk {namespace ui {
    auto
    newline()
        -> void {
        puts("");
    }

    auto
    userprompt()
        -> void {
        printf(">>> ");
    }

    auto
    divider()
        -> void {
        newline();
        puts("─────────────────────────────────────────");
        newline();
    }

    auto
    print_welcome()
        -> void {
        puts("Welcome, farmer!");
        newline();
        puts("You have been tasked with the development of three key farms:");
        puts("* Strawberry");
        puts("* Elderberry");
        puts("* Watermelon");
        newline();
        puts("You must grow fruit and sell it to customers.");
        puts("Your customers can grow tired, so don't keep them waiting!");
        puts("Your goal is to earn enough to buy the title of 'Best Farmer'.");
        puts("Good luck!");

        divider();
    }

    auto
    print_farmer_data(
        farmer &the_farmer
    )
        -> void {
        puts("Farmer, here is your information:");
        printf("- Cash: $%.2f\n", the_farmer.get_money());

        printf(
            "- Has strawberry farm: %s\n",
            util::bool_to_affirmation(true).c_str()
        );

        printf(
            "- Has elderberry farm: %s\n",
            util::bool_to_affirmation(the_farmer.has_elderberry_farm()).c_str()
        );

        printf(
            "- Has watermelon farm: %s\n",
            util::bool_to_affirmation(the_farmer.has_watermelon_farm()).c_str()
        );

        divider();
    }

    auto
    ff_ui(
        farmer &the_farmer
    )
        -> void {
        int days;
        do {
            puts("How many days?");

            userprompt();
            std::cin >> days;

            if (days < 0) {
                puts("You can't go back in time.");
            }

            if (days == 0) {
                puts("Congratulations. Nothing happened.");
            }

            divider();
        } while (days < 0);

        the_farmer.tick(days);
    }

    auto
    menu_ui(
        const farmer &the_farmer
    )
        -> int {
        const int available_options = 5 + (the_farmer.has_elderberry_farm()
                                               ? 1
                                               : 0) + (
                                          the_farmer.has_watermelon_farm()
                                              ? 1
                                              : 0);

        puts("What would you like to do?");

        int choice;
        do {
            puts("Please choose an option:");
            puts("0) Exit");
            puts("1) Print stats");
            puts("2) Fast forward time");
            puts("3) Open the shop");
            puts("4) Open the requests menu");
            puts("5) Check strawberry farm");

            if (the_farmer.has_elderberry_farm()) {
                puts("6) Check elderberry farm");
            }

            if (the_farmer.has_watermelon_farm()) {
                puts("7) Check watermelon farm");
            }

            userprompt();
            std::cin >> choice;

            divider();
        } while (choice < 0 || choice > available_options);

        return choice;
    }

    auto
    confirm_purchase_ui(
        const farmer &the_farmer,
        const double  amt
    )
        -> bool {
        printf("The transaction will cost $%.2f\n", amt);

        if (the_farmer.get_money() < amt) {
            puts("You do not have enough money for this.");
            return false;
        }

        int confirmation;
        do {
            puts("Confirm?");
            puts("0) No");
            puts("1) Yes");

            userprompt();
            std::cin >> confirmation;

            divider();
        } while (confirmation < 0 || confirmation > 1);

        return confirmation == 1;
    }

    auto
    shop_ui(
        const farmer &farmer
    )
        -> void {
        puts("Welcome to the shop!");
        puts("What will you buy?");
    }

    auto
    requests_ui(
        const farmer &farmer
    )
        -> void {
    }

    auto
    crop_growth_purchase_ui()
        -> std::pair<double, int> {
        bool   valid_water = false;
        bool   valid_days  = false;
        double water_units;
        int    days_to_grow;

        do {
            puts("How many water units will you add?");

            userprompt();
            std::cin >> water_units;

            if (water_units <= 0) {
                puts("You need to provide a water amount greater than 0");
                continue;
            }

            divider();

            valid_water = true;
        } while (!valid_water);

        do {
            puts("How many days will you water it for?");

            userprompt();
            std::cin >> days_to_grow;

            if (days_to_grow <= 0) {
                puts("You need to provide an amount of days greater than 0");
                continue;
            }

            newline();

            valid_days = true;
        } while (!valid_days);

        divider();

        return std::make_pair(water_units, days_to_grow);
    }

    auto
    generic_farm_ui(
        std::string const &name
    )
        -> int {
        printf("Welcome to the %s farm\n", name.c_str());

        int choice;
        do {
            puts("Please choose an option:");
            puts("0) Exit");
            puts("1) Print farm crops");
            printf("2) Grow a %s\n", name.c_str());
            puts("3) Clear ill crops\n");

            userprompt();
            std::cin >> choice;

            divider();
        } while (choice < 0 || choice > 3);

        return choice;
    }

    auto
    strawberry_farm_ui(
        farmer &the_farmer
    )
        -> void {
        strawberry_farm &farm = the_farmer.get_strawberry_farm();

        int choice;
        do {
            choice = generic_farm_ui("strawberry");
            switch (choice) {
                case 1: {
                    farm.print_fruit();
                    divider();
                    break;
                }
                case 2: {
                    const std::pair<double, int> growth_data =
                        crop_growth_purchase_ui();

                    const double water_cost =
                        growth_data.first * COST_PER_WATER_UNIT;

                    const bool will_buy = confirm_purchase_ui(
                        the_farmer,
                        water_cost
                    );

                    if (will_buy) {
                        the_farmer.sub_money(water_cost);
                        farm.grow_strawberry(
                            growth_data.first,
                            growth_data.second
                        );
                    }
                    break;
                }
                case 3: {
                    farm.remove_ill_fruit();
                    break;
                }
                default: {
                    break;
                }
            }
        } while (choice != 0);

        divider();
    }

    auto
    elderberry_farm_ui(
        farmer &the_farmer
    )
        -> void {
        elderberry_farm &farm = the_farmer.get_elderberry_farm();

        int choice;
        do {
            choice = generic_farm_ui("elderberry");
            switch (choice) {
                case 1: {
                    farm.print_fruit();
                    divider();
                    break;
                }
                case 2: {
                    const std::pair<double, int> growth_data =
                        crop_growth_purchase_ui();

                    const double water_cost =
                        growth_data.first * COST_PER_WATER_UNIT;

                    const bool will_buy = confirm_purchase_ui(
                        the_farmer,
                        water_cost
                    );

                    if (will_buy) {
                        the_farmer.sub_money(water_cost);
                        farm.grow_elderberry(
                            growth_data.first,
                            growth_data.second
                        );
                    }
                    break;
                }
                case 3: {
                    farm.remove_ill_fruit();
                    break;
                }
                default: {
                    break;
                }
            }
        } while (choice != 0);

        divider();
    }

    auto
    watermelon_farm_ui(
        farmer &the_farmer
    )
        -> void {
        watermelon_farm &farm = the_farmer.get_watermelon_farm();

        int choice;
        do {
            choice = generic_farm_ui("watermelon");
            switch (choice) {
                case 1: {
                    farm.print_fruit();
                    divider();
                    break;
                }
                case 2: {
                    const std::pair<double, int> growth_data =
                        crop_growth_purchase_ui();

                    const double water_cost =
                        growth_data.first * COST_PER_WATER_UNIT;

                    const bool will_buy = confirm_purchase_ui(
                        the_farmer,
                        water_cost
                    );

                    if (will_buy) {
                        the_farmer.sub_money(water_cost);
                        farm.grow_watermelon(
                            growth_data.first,
                            growth_data.second
                        );
                    }
                    break;
                }
                case 3: {
                    farm.remove_ill_fruit();
                    break;
                }
                default: {
                    break;
                }
            }
        } while (choice != 0);

        divider();
    }
}}
