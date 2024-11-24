#ifndef REQUEST_GENERATOR_HH
#define REQUEST_GENERATOR_HH
#include <stdexcept>
#include <utility>

#include "farmer.hh"
#include "fruit.hh"

namespace fmk {
    enum class request_kind {
        STRAWBERRY,
        ELDERBERRY,
        WATERMELON
    };

    auto
    int_to_rkind(
        int ikind
    )
        -> request_kind;

    auto
    rkind_to_str(
        request_kind rkind
    )
        -> std::string;

    class request_generator {
    public:
        explicit
        request_generator();

        auto
        tick(
            int days
        )
            -> void;

        auto
        regenerate_requests(
            const farmer &farmer
        )
            -> void;

        [[nodiscard]] auto
        get_request_1()
            -> std::pair<request_kind, std::pair<double, int>> &;

        [[nodiscard]] auto
        get_request_2()
            -> std::pair<request_kind, std::pair<double, int>> &;

        [[nodiscard]] auto
        get_request_3()
            -> std::pair<request_kind, std::pair<double, int>> &;

    private:
        std::pair<request_kind, std::pair<double, int>> _req_1;
        std::pair<request_kind, std::pair<double, int>> _req_2;
        std::pair<request_kind, std::pair<double, int>> _req_3;
    };
}

#endif //REQUEST_GENERATOR_HH
