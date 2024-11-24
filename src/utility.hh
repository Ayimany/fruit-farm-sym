#ifndef UTILITY_HH
#define UTILITY_HH
#include <stdexcept>
#include <string>

namespace fmk { namespace util {
    [[nodiscard]] auto
    bool_to_affirmation(
        bool b
    )
        -> std::string;

    template <typename... types_tp>
    [[nodiscard]] auto
    strfmt(
        std::string const &format,
        types_tp...        args
    ) noexcept(false)
        -> std::string {
        const int sz = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;

        if (sz <= 0) {
            throw std::runtime_error("Formatting error");
        }

        const auto nsz    = static_cast<size_t>(sz);
        const auto buffer = new char[nsz]();
        std::snprintf(buffer, nsz, format.c_str(), args...);

        auto output = std::string(buffer);
        delete[] (buffer);

        return output;
    }
}}

#endif //UTILITY_HH
