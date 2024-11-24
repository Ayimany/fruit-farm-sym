#include "utility.hh"

namespace fmk { namespace util {
    auto
    bool_to_affirmation(
        const bool b
    )
        -> std::string {
        return b
                   ? "Yes"
                   : "No";
    }
}}
