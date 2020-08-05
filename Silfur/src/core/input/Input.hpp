#pragma once

#ifndef __SILFUR_CORE_INPUT_HPP__
#define __SILFUR_CORE_INPUT_HPP__

#include "core/Base.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

#include <utility>

namespace Silfur
{
    class Window;

    class Input
    {
    public:
        static bool IsKeyPressed(VKey p_key);
        static bool IsKeyPressed(ScanCode p_scancode);
        static std::string GetKeyName(VKey p_key);
        static std::string GetKeyName(ScanCode p_scancode);
        static ScanCode ToScanCode(VKey p_key);
        static VKey ToVirtualKey(ScanCode p_scancode);

        static bool IsMouseButtonPressed(MouseButton p_button);
        static std::pair<int, int> GetMousePosition();
        static std::pair<int, int> GetMousePositionRelativeToFocusWindow();
        static std::pair<int, int> GetMouseRelativePosition();
        static bool SetRelativeMouseMode(bool p_enabled);
    };
}

#endif // __SILFUR_CORE_INPUT_HPP__
