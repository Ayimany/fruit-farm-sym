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
    ff_ui(
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
    menu_ui(
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
    confirm_purchase_ui(
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
    shop_ui(
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
                printf("1) Elderberry Farm: $%.2f\n", ELDERBERRY_FARM_COST);
            }

            if (!the_farmer.has_watermelon_farm()) {
                printf("2) Watermelon Farm: $%.2f\n", WATERMELON_FARM_COST);
            }

            if (!the_farmer.is_best_farmer()) {
                printf("3) Best Farmer Title: $%.2f\n", BEST_FARMER_COST);
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

                    const bool will_buy = confirm_purchase_ui(
                        the_farmer,
                        ELDERBERRY_FARM_COST
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

                    const bool will_buy = confirm_purchase_ui(
                        the_farmer,
                        WATERMELON_FARM_COST
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

                    const bool will_buy = confirm_purchase_ui(
                        the_farmer,
                        BEST_FARMER_COST
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
    display_request(
        const std::pair<request_kind, std::pair<double, int>> &request
    )
        -> void {
        divider();

        std::string const kind_str        = rkind_to_str(request.first);
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
    requests_ui(
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
                    generator.regenerate_requests(the_farmer);
                    break;
                }
                case 2: {
                    display_request(generator.get_request_1());
                    display_request(generator.get_request_2());
                    display_request(generator.get_request_3());
                    break;
                }
                case 3: {
                    request_fetching_ui(the_farmer, generator);
                    break;
                }
                default: {
                    break;
                }
            }
        } while (choice != 0);
    }

    auto
    request_validation_note(
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
    request_fetching_ui(
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
                    request_validation_note(request);
                    request_fulfilment_ui(the_farmer, request);
                    break;
                }
                case 2: {
                    std::pair<request_kind, std::pair<double, int>> &request =
                        generator.get_request_2();
                    request_validation_note(request);
                    request_fulfilment_ui(the_farmer, request);
                    break;
                }
                case 3: {
                    std::pair<request_kind, std::pair<double, int>> &request =
                        generator.get_request_3();
                    request_validation_note(request);
                    request_fulfilment_ui(the_farmer, request);
                    break;
                }
                default: {
                    continue;
                }
            }
        } while (choice != 0);
    }

    auto
    request_fulfilment_ui(
        farmer &                                         the_farmer,
        std::pair<request_kind, std::pair<double, int>> &request
    )
        -> void {
        divider();
        switch (request.first) {
            case request_kind::STRAWBERRY: {
                strawberry_farm &farm = the_farmer.get_strawberry_farm();

                const bool has_fruit = farm.get_fruit_count() != 0;

                if (!has_fruit) {
                    puts("You have no strawberries to offer.");
                    break;
                }

                farm.print_fruit();
                divider();

                puts("Which strawberries will you offer? Type their number");
                puts("Type 0 to stop offering");

                int index;
                do {
                    userprompt();
                    std::cin >> index;

                    if (index <= 0 || index > farm.get_fruit_count()) {
                        puts("Invalid strawberry");
                        newline();
                        continue;
                    }

                    index--;

                    strawberry &fruit = farm.get_fruit(index);

                    if (fruit.is_spoiled()) {
                        puts("You cannot offer this strawberry!");
                        newline();
                        continue;
                    }

                    request.second.first -= fruit.get_weight();

                    const double cash = farm.sell_strawberry(index);
                    the_farmer.add_money(cash);

                    printf("* Sold for $%.2f\n", cash);
                } while (index != 0 && request.second.second > 0);

                break;
            }
            case request_kind::ELDERBERRY: {
                elderberry_farm &farm = the_farmer.get_elderberry_farm();

                const bool has_fruit = farm.get_fruit_count() != 0;
                const bool has_farm  = the_farmer.has_elderberry_farm();

                if (!has_fruit || !has_farm) {
                    puts("You have no elderberries to offer.");
                    break;
                }

                farm.print_fruit();
                divider();

                puts("Which elderberries will you offer? Type their number");
                puts("Type 0 to stop offering");

                int index;
                do {
                    userprompt();
                    std::cin >> index;

                    if (index <= 0 || index > farm.get_fruit_count()) {
                        puts("Invalid elderberry");
                        newline();
                        continue;
                    }

                    index--;

                    elderberry &fruit = farm.get_fruit(index);

                    if (fruit.is_spoiled()) {
                        puts("You cannot offer this elderberry!");
                        newline();
                        continue;
                    }

                    request.second.first -= fruit.get_weight();

                    const double cash = farm.sell_elderberry(index);
                    the_farmer.add_money(cash);

                    printf("* Sold for $%.2f\n", cash);
                } while (index != 0 && request.second.second > 0);

                break;
            }
            case request_kind::WATERMELON: {
                watermelon_farm &farm = the_farmer.get_watermelon_farm();

                const bool has_fruit = farm.get_fruit_count() != 0;
                const bool has_farm  = the_farmer.has_watermelon_farm();

                if (!has_fruit || !has_farm) {
                    puts("You have no watermelons to offer.");
                    break;
                }

                farm.print_fruit();
                divider();

                puts("Which watermelons will you offer? Type their number");
                puts("Type 0 to stop offering");

                int index;
                do {
                    userprompt();
                    std::cin >> index;

                    if (index <= 0 || index > farm.get_fruit_count()) {
                        puts("Invalid watermelon");
                        newline();
                        continue;
                    }

                    index--;

                    watermelon &fruit = farm.get_fruit(index);

                    if (fruit.is_spoiled()) {
                        puts("You cannot offer this watermelon!");
                        newline();
                        continue;
                    }

                    request.second.first -= fruit.get_weight();

                    const double cash = farm.sell_watermelon(index);
                    the_farmer.add_money(cash);

                    printf("* Sold for $%.2f\n", cash);
                } while (index != 0 && request.second.second > 0);

                break;
            }
        }

        if (request.second.second <= 0) {
            puts("You have fulfilled this request entirely");
            printf(
                "You will be awarded an extra $%.2f\n",
                SUCCESSFUL_REQUEST_BONUS
            );

            request.second.second = 0.0;
            the_farmer.add_money(SUCCESSFUL_REQUEST_BONUS);
        }
    }

    auto
    crop_growth_purchase_ui()
        -> std::pair<double, int> {
        bool   valid_water = false;
        bool   valid_days  = false;
        double water_units;
        int    days_to_grow;

        divider();

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

        return std::make_pair(water_units, days_to_grow);
    }

    auto
    generic_farm_ui(
        std::string const &name
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
                    divider();
                    farm.print_fruit();
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
    }
}}
