#include "request_generator.hh"

#include <random>

#include "constants.hh"
#include "farmer.hh"

namespace fmk {
    auto
    request_kind_to_str(
        const request_kind request_kind
    )
        -> std::string {
        switch (request_kind) {
            case request_kind::STRAWBERRY: {
                return "strawberry";
            }
            case request_kind::ELDERBERRY: {
                return "elderberry";
            }
            case request_kind::WATERMELON: {
                return "watermelon";
            }
        }

        throw std::runtime_error { "Invalid request kind" };
    }

    auto
    int_to_request_kind(
        int const integer
    )
        -> request_kind {
        switch (integer) {
            case 1: {
                return request_kind::STRAWBERRY;
            }
            case 2: {
                return request_kind::ELDERBERRY;
            }
            case 3: {
                return request_kind::WATERMELON;
            }
            default: {
                throw std::invalid_argument { "Invalid request kind" };
            }
        }
    }

    request_generator::request_generator()
        : _req_1 { request_kind::STRAWBERRY, { 0, 0 } }
        , _req_2 { request_kind::STRAWBERRY, { 0, 0 } }
        , _req_3 { request_kind::STRAWBERRY, { 0, 0 } } {
    }

    auto
    request_generator::tick(
        const int days
    )
        -> void {
        _req_1.second.second = std::max(_req_1.second.second - days, 0);
        _req_2.second.second = std::max(_req_2.second.second - days, 0);
        _req_3.second.second = std::max(_req_3.second.second - days, 0);
    }

    auto
    request_generator::regenerate_requests(
        const int farmer_level
    )
        -> void {
        const int max_kind = farmer_level;

        std::random_device dev { };
        std::mt19937       gen { dev() };

        std::uniform_int_distribution<int> kind_dist { 1, max_kind };

        std::uniform_int_distribution<int> day_dist {
            constants::MIN_REQUEST_DAYS,
            constants::MAX_REQUEST_DAYS
        };

        std::uniform_real_distribution<double> weight_dist {
            constants::MIN_REQUEST_DAYS,
            constants::MAX_REQUEST_WEIGHT
        };

        _req_1 = std::make_pair(
            int_to_request_kind(kind_dist(gen)),
            std::make_pair(weight_dist(gen), day_dist(gen))
        );

        _req_2 = std::make_pair(
            int_to_request_kind(kind_dist(gen)),
            std::make_pair(weight_dist(gen), day_dist(gen))
        );

        _req_3 = std::make_pair(
            int_to_request_kind(kind_dist(gen)),
            std::make_pair(weight_dist(gen), day_dist(gen))
        );
    }

    auto
    request_generator::get_request_1()
        -> std::pair<request_kind, std::pair<double, int>> & {
        return _req_1;
    }

    auto
    request_generator::get_request_2()
        -> std::pair<request_kind, std::pair<double, int>> & {
        return _req_2;
    }

    auto
    request_generator::get_request_3()
        -> std::pair<request_kind, std::pair<double, int>> & {
        return _req_3;
    }
}
