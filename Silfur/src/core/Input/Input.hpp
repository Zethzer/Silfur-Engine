#pragma once

#ifndef __SILFUR_CORE_INPUT_HPP__
#define __SILFUR_CORE_INPUT_HPP__

#include "core/Base.hpp"
#include "KeyCodes.hpp"
#include "MouseCodes.hpp"

#include <utility>

namespace Silfur
{
    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode p_key);
        static const char* GetKeyName(KeyCode p_key);

        static bool IsMouseButtonPressed(MouseCode p_button);
        static std::pair<float, float> GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };
}

#endif // __SILFUR_CORE_INPUT_HPP__
