#ifndef REQUEST_GENERATOR_HH
#define REQUEST_GENERATOR_HH
#include <utility>

#include "fruit.hh"

namespace fmk {
    /**
     * Determines the type of fruit a person is requesting
     */
    enum class request_kind {
        STRAWBERRY,
        ELDERBERRY,
        WATERMELON
    };

    /**
     * Converts an integer to a request kind
     * @param integer The integer
     * @return The request kind
     */
    auto
    int_to_request_kind(
        int integer
    )
        -> request_kind;

    /**
     * Converts a request kind to a string
     * @param request_kind The request kind
     * @return The request kind, as a string
     */
    auto
    request_kind_to_str(
        request_kind request_kind
    )
        -> std::string;

    /**
     * Generates requests for the farmer to fulfill
     */
    class request_generator {
    public:
        /**
         * Constructs a request generator
         */
        explicit
        request_generator();

        /**
         * Makes time go forward
         * @param days The amount of days
         */
        auto
        tick(
            int days
        )
            -> void;

        /**
         * Regenerates the available requests based on the farmer's level
         * @param farmer_level The farmer's level
         */
        auto
        regenerate_requests(
            int farmer_level
        )
            -> void;

        /**
         * Returns request 1
         * @return Request 1
         */
        [[nodiscard]] auto
        get_request_1()
            -> std::pair<request_kind, std::pair<double, int>> &;

        /**
         * Returns request 2
         * @return Request 2
         */
        [[nodiscard]] auto
        get_request_2()
            -> std::pair<request_kind, std::pair<double, int>> &;

        /**
         * Returns request 3
         * @return Request 3
         */
        [[nodiscard]] auto
        get_request_3()
            -> std::pair<request_kind, std::pair<double, int>> &;

    private:
        /// Request 1
        std::pair<request_kind, std::pair<double, int>> _req_1;

        /// Request 2
        std::pair<request_kind, std::pair<double, int>> _req_2;

        /// Request 3
        std::pair<request_kind, std::pair<double, int>> _req_3;
    };
}

#endif //REQUEST_GENERATOR_HH
