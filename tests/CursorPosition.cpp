#include "AsyncCommit.hpp"
#include "Shared.hpp"
#include "shared.hpp"

#include <cmath>

using namespace Aquamarine;
using Hyprutils::Math::Vector2D;

int main() {
    int ret = 0;

    // A driver rebuilds the pointer as CRTC_X + HOTSPOT_X, with HOTSPOT_X = floor(hotspot).
    const Vector2D HOTSPOT = {1.5, 2.75};
    const auto     PLANE   = cursorPlanePosition({100.25, 50.5}, HOTSPOT);
    EXPECT(PLANE.x + std::floor(HOTSPOT.x), 100.0);
    EXPECT(PLANE.y + std::floor(HOTSPOT.y), 50.0);

    EXPECT(cursorPlanePosition({-0.5, -1.25}, {0, 0}).x, -1.0);
    EXPECT(cursorPlanePosition({-0.5, -1.25}, {0, 0}).y, -2.0);

    // Late async updates go through the mailbox, and must land where an ordinary commit would.
    CDRMCursorPositionMailbox mailbox;
    mailbox.store({-0.5, 10.75});
    EXPECT(mailbox.load().x, -1.0);
    EXPECT(mailbox.load().y, 10.0);
    EXPECT(cursorPlanePosition(mailbox.load(), HOTSPOT).x, cursorPlanePosition({-0.5, 10.75}, HOTSPOT).x);
    EXPECT(cursorPlanePosition(mailbox.load(), HOTSPOT).y, cursorPlanePosition({-0.5, 10.75}, HOTSPOT).y);

    return ret;
}
