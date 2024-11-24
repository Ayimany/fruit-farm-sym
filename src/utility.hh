#ifndef UTILITY_HH
#define UTILITY_HH
#include <stdexcept>
#include <string>

namespace fmk { namespace util {
    /**
     * Converts a bool to "Yes" or "No"
     * @param b
     * @return
     */
    [[nodiscard]] auto
    bool_to_affirmation(
        bool b
    )
        -> std::string;

    /**
     * Formats a string and returns it
     * @tparam types_tp The types of the formatting elements
     * @param format The format
     * @param args The arguments to format
     * @return The formatted string
     */
    template <typename... types_tp>
    [[nodiscard]] auto
    strfmt(
        std::string const &format,
        types_tp...        args
    ) noexcept(false)
        -> std::string {
        // Get target size + '\0'
        const int sz = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;

        if (sz <= 0) {
            throw std::runtime_error { "Formatting error" };
        }

        // Create buffer and write to it
        const auto nsz    = static_cast<size_t>(sz);
        const auto buffer = new char[nsz]();
        std::snprintf(buffer, nsz, format.c_str(), args...);

        // Copy buffer as std::string, delete old buffer
        std::string output { buffer };
        delete[] (buffer);

        return output;
    }
}}

#endif //UTILITY_HH
