#pragma once

#ifndef __SILFUR_CORE_INPUT_HPP__
#define __SILFUR_CORE_INPUT_HPP__

#include "core/Base.hpp"
#include "Keyboard.hpp"
#include "MouseCodes.hpp"

#include <utility>

namespace Silfur
{
    class Input
    {
    public:
        static bool IsKeyPressed(VKey p_key);
        static bool IsKeyPressed(ScanCode p_scancode);
        static std::string GetKeyName(VKey p_key);
        static std::string GetKeyName(ScanCode p_scancode);
        static ScanCode ToScanCode(VKey p_key);
        static VKey ToVirtualKey(ScanCode p_scancode);

        /*static bool IsMouseButtonPressed(MouseCode p_button);
        static std::pair<float, float> GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();*/
    };
}

#endif // __SILFUR_CORE_INPUT_HPP__
