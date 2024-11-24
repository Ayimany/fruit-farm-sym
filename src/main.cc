#include "constants.hh"
#include "farmer.hh"
#include "system_ui.hh"

int
main() {
    fmk::ui::print_welcome();
    fmk::farmer farmer(fmk::FARMER_STARTING_CASH);

    int choice;
    do {
        choice = fmk::ui::menu_ui(farmer);

        switch (choice) {
            case 1: {
                fmk::ui::print_farmer_data(farmer);
                break;
            }

            case 2: {
                fmk::ui::ff_ui(farmer);
                break;
            }

            case 3: {
                fmk::ui::shop_ui(farmer);
                break;
            }

            case 4: {
                fmk::ui::requests_ui(farmer);
                break;
            }

            case 5: {
                fmk::ui::strawberry_farm_ui(farmer);
                break;
            }

            case 6: {
                fmk::ui::elderberry_farm_ui(farmer);
                break;
            }

            case 7: {
                fmk::ui::watermelon_farm_ui(farmer);
                break;
            }

            default: {
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
