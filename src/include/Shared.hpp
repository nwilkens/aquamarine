#pragma once

#include <iostream>
#include <format>
#include <signal.h>
#include <cmath>
#include <hyprutils/math/Vector2D.hpp>

namespace Aquamarine {
    bool envEnabled(const std::string& env);
    bool envExplicitlyDisabled(const std::string& env);
    bool isTrace();

    // A cursor plane's CRTC_X/Y. Drivers with hotspot properties add HOTSPOT_X/Y back,
    // so both are floored alike and sum to the floored pointer position.
    inline Hyprutils::Math::Vector2D cursorPlanePosition(const Hyprutils::Math::Vector2D& pos, const Hyprutils::Math::Vector2D& hotspot) {
        return {std::floor(pos.x) - std::floor(hotspot.x), std::floor(pos.y) - std::floor(hotspot.y)};
    }
};

#define RASSERT(expr, reason, ...)                                                                                                                                                 \
    if (!(expr)) {                                                                                                                                                                 \
        std::cout << std::format("\n==========================================================================================\nASSERTION FAILED! \n\n{}\n\nat: line {} in {}",    \
                                 std::format(reason, ##__VA_ARGS__), __LINE__,                                                                                                     \
                                 ([]() constexpr -> std::string { return std::string(__FILE__).substr(std::string(__FILE__).find_last_of('/') + 1); })());                         \
        std::cout << "[Aquamarine] Assertion failed!";                                                                                                                             \
        raise(SIGABRT);                                                                                                                                                            \
    }

#define ASSERT(expr) RASSERT(expr, "?")

#define TRACE(expr)                                                                                                                                                                \
    {                                                                                                                                                                              \
        if (Aquamarine::isTrace()) {                                                                                                                                               \
            expr;                                                                                                                                                                  \
        }                                                                                                                                                                          \
    }
