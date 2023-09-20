#pragma once

#include "defines.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

#include <utility>

namespace Silfur
{
    class Window;

    class Input
    {
    public:
        static bool IsKeyPressed(VKey key);
        static bool IsKeyPressed(ScanCode scancode);
        static std::string GetKeyName(VKey key);
        static std::string GetKeyName(ScanCode scancode);
        static std::string GetScanCodeName(ScanCode scancode);
        static ScanCode ToScanCode(VKey key);
        static VKey ToVirtualKey(ScanCode scancode);

        static bool IsMouseButtonPressed(MouseButton button);
        static std::pair<int, int> GetMousePosition();
        static std::pair<int, int> GetMousePositionRelativeToFocusWindow();
        static std::pair<int, int> GetMouseRelativePosition();
        static bool SetRelativeMouseMode(bool enabled);
    };
}
