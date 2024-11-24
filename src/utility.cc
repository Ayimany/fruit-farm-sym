//
// Created by ayimany on 11/23/24.
//

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
