#include "constants.hh"
#include "farmer.hh"
#include "request_generator.hh"
#include "system_ui.hh"

int
main() {
    fmk::farmer            farmer { fmk::constants::FARMER_STARTING_CASH };
    fmk::request_generator request_generator;

    request_generator.regenerate_requests(farmer.get_level());

    fmk::ui::print_welcome();

    int choice;
    do {
        choice = fmk::ui::print_menu_ui(farmer);

        switch (choice) {
            case 1: {
                fmk::ui::print_farmer_data(farmer);
                break;
            }

            case 2: {
                fmk::ui::print_fast_forward_ui(farmer, request_generator);
                break;
            }

            case 3: {
                fmk::ui::print_shop_ui(farmer);
                break;
            }

            case 4: {
                fmk::ui::print_requests_ui(farmer, request_generator);
                break;
            }

            case 5: {
                fmk::ui::print_generic_farm_ui(
                    "strawberry",
                    farmer,
                    farmer.get_strawberry_farm()
                );
                break;
            }

            case 6: {
                fmk::ui::print_generic_farm_ui(
                    "elderberry",
                    farmer,
                    farmer.get_elderberry_farm()
                );
                break;
            }

            case 7: {
                fmk::ui::print_generic_farm_ui(
                    "watermelon",
                    farmer,
                    farmer.get_watermelon_farm()
                );
                break;
            }

            default: {
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
