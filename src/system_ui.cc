#include "system_ui.hh"
#include <iostream>

#include "constants.hh"
#include "request_generator.hh"
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
        divider();
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
    }

    auto
    print_farmer_data(
        const farmer &the_farmer
    )
        -> void {
        divider();

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

        puts(
            the_farmer.is_best_farmer()
                ? "You ARE the best farmer! :)"
                : "You are currently NOT the best farmer :("
        );
    }

    auto
    print_fast_forward_ui(
        farmer &           the_farmer,
        request_generator &generator
    )
        -> void {
        divider();

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
        } while (days < 0);

        the_farmer.tick(days);
        generator.tick(days);
    }

    auto
    print_menu_ui(
        const farmer &the_farmer
    )
        -> int {
        divider();

        const int available_options = 5 + (the_farmer.has_elderberry_farm()
                                               ? 1
                                               : 0) + (
                                          the_farmer.has_watermelon_farm()
                                              ? 1
                                              : 0);

        puts("What would you like to do?");

        int choice;
        do {
            divider();
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
        } while (choice < 0 || choice > available_options);

        return choice;
    }

    auto
    print_purchase_confirmation_ui(
        const farmer &the_farmer,
        const double  amt
    )
        -> bool {
        divider();

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
        } while (confirmation < 0 || confirmation > 1);

        return confirmation == 1;
    }

    auto
    print_shop_ui(
        farmer &the_farmer
    )
        -> void {
        int choice;
        do {
            divider();

            puts("Welcome to the shop!");
            puts("What will you buy?");
            puts("0) Exit");

            if (!the_farmer.has_elderberry_farm()) {
                printf(
                    "1) Elderberry Farm: $%.2f\n",
                    constants::ELDERBERRY_FARM_COST
                );
            }

            if (!the_farmer.has_watermelon_farm()) {
                printf(
                    "2) Watermelon Farm: $%.2f\n",
                    constants::WATERMELON_FARM_COST
                );
            }

            if (!the_farmer.is_best_farmer()) {
                printf(
                    "3) Best Farmer Title: $%.2f\n",
                    constants::BEST_FARMER_COST
                );
            }
            userprompt();
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    if (the_farmer.has_elderberry_farm()) {
                        divider();
                        puts("You already own this item");
                        break;
                    }

                    const bool will_buy = print_purchase_confirmation_ui(
                        the_farmer,
                        constants::ELDERBERRY_FARM_COST
                    );

                    if (will_buy) {
                        the_farmer.enable_elderberry_farm();
                    }
                    break;
                }

                case 2: {
                    if (the_farmer.has_watermelon_farm()) {
                        divider();
                        puts("You already own this item");
                        break;
                    }

                    const bool will_buy = print_purchase_confirmation_ui(
                        the_farmer,
                        constants::WATERMELON_FARM_COST
                    );

                    if (will_buy) {
                        the_farmer.enable_watermelon_farm();
                    }
                    break;
                }

                case 3: {
                    if (the_farmer.is_best_farmer()) {
                        divider();
                        puts("You are already the best farmer :)");
                        break;
                    }

                    const bool will_buy = print_purchase_confirmation_ui(
                        the_farmer,
                        constants::BEST_FARMER_COST
                    );

                    if (will_buy) {
                        the_farmer.become_best_farmer();
                    }
                    break;
                }
                default: {
                    break;
                }
            }
        } while (choice != 0);
    }

    auto
    print_request_display_element(
        const std::pair<request_kind, std::pair<double, int>> &request
    )
        -> void {
        divider();

        std::string const kind_str        = request_kind_to_str(request.first);
        int const         days_to_fulfill = request.second.second;
        bool const        can_fulfill     = days_to_fulfill > 0;
        double const      weight          = request.second.first;

        puts("Request:");
        printf("* Solicits: %s\n", kind_str.c_str());
        printf("* Weight: %s\n", util::strfmt("%.2f kg", weight).c_str());

        if (can_fulfill) {
            printf("* Days to fulfill: %d\n", days_to_fulfill);
        } else {
            puts("* EXPIRED");
        }
    }

    auto
    print_requests_ui(
        farmer &           the_farmer,
        request_generator &generator
    )
        -> void {
        int choice;
        do {
            divider();

            puts("What would you like to do?");
            puts("0) Exit");
            puts("1) Regenerate requests (takes 3 days)");
            puts("2) View Requests");
            puts("3) Fulfill Request");

            userprompt();
            std::cin >> choice;

            switch (choice) {
                case 0: {
                    return;
                }
                case 1: {
                    the_farmer.tick(3);
                    generator.regenerate_requests(the_farmer.get_level());
                    break;
                }
                case 2: {
                    print_request_display_element(generator.get_request_1());
                    print_request_display_element(generator.get_request_2());
                    print_request_display_element(generator.get_request_3());
                    break;
                }
                case 3: {
                    print_request_fetching_ui(the_farmer, generator);
                    break;
                }
                default: {
                    break;
                }
            }
        } while (choice != 0);
    }

    auto
    print_request_validation_note_element(
        const std::pair<request_kind, std::pair<double, int>> &request
    )
        -> bool {
        if (request.second.second == 0) {
            puts("This request has expired.");
            return false;
        }

        if (request.second.first <= 0) {
            puts("This request has already been fulfilled.");
            return false;
        }

        return true;
    }

    auto
    print_request_fetching_ui(
        farmer &           the_farmer,
        request_generator &generator
    )
        -> void {
        int choice;
        do {
            divider();

            puts("Which request?");
            puts("0) Exit");
            puts("1) Request 1");
            puts("2) Request 2");
            puts("3) Request 3");

            userprompt();
            std::cin >> choice;

            // Repetition is somewhat necessary here due to reference handling
            switch (choice) {
                case 0: {
                    return;
                }
                case 1: {
                    std::pair<request_kind, std::pair<double, int>> &request =
                        generator.get_request_1();
                    const bool can_access = print_request_validation_note_element(request);
                    if (can_access) {
                        print_request_fulfilment_ui(the_farmer, request);
                    }
                    break;
                }
                case 2: {
                    std::pair<request_kind, std::pair<double, int>> &request =
                        generator.get_request_2();
                    const bool can_access = print_request_validation_note_element(request);
                    if (can_access) {
                        print_request_fulfilment_ui(the_farmer, request);
                    }
                    break;
                }
                case 3: {
                    std::pair<request_kind, std::pair<double, int>> &request =
                        generator.get_request_3();
                    const bool can_access = print_request_validation_note_element(request);
                    if (can_access) {
                        print_request_fulfilment_ui(the_farmer, request);
                    }
                    break;
                }
                default: {
                }
            }
        } while (choice != 0);
    }

    auto
    print_request_fulfilment_ui(
        farmer &                                         the_farmer,
        std::pair<request_kind, std::pair<double, int>> &request
    )
        -> void {
        divider();
        switch (request.first) {
            case request_kind::STRAWBERRY: {
                print_request_transfer_ui(
                    the_farmer,
                    the_farmer.get_strawberry_farm(),
                    request
                );
                break;
            }
            case request_kind::ELDERBERRY: {
                print_request_transfer_ui(
                    the_farmer,
                    the_farmer.get_elderberry_farm(),
                    request
                );
                break;
            }
            case request_kind::WATERMELON: {
                print_request_transfer_ui(
                    the_farmer,
                    the_farmer.get_watermelon_farm(),
                    request
                );
                break;
            }
        }

        if (request.second.second <= 0) {
            puts("You have fulfilled this request entirely");
            printf(
                "You will be awarded an extra $%.2f\n",
                constants::SUCCESSFUL_REQUEST_BONUS
            );

            request.second.second = 0.0;
            the_farmer.add_money(constants::SUCCESSFUL_REQUEST_BONUS);
        }
    }

    auto
    print_crop_growth_params_ui()
        -> std::pair<int, double> {
        bool   valid_water = false;
        bool   valid_days  = false;
        double water_units;
        int    days_to_grow;

        divider();

        do {
            puts("How many days will you water it for?");

            userprompt();
            std::cin >> days_to_grow;

            if (days_to_grow <= 0) {
                puts("You need to provide an amount of days greater than 0");
                continue;
            }

            valid_days = true;
        } while (!valid_days);

        do {
            puts("How many water units will you add?");

            userprompt();
            std::cin >> water_units;

            if (water_units <= 0) {
                puts("You need to provide a water amount greater than 0");

                continue;
            }

            valid_water = true;
        } while (!valid_water);

        return std::make_pair(days_to_grow, water_units);
    }
}}
