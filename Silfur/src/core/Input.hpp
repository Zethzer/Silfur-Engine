#pragma once

#ifndef __SILFUR_CORE_INPUT_HPP__
#define __SILFUR_CORE_INPUT_HPP__

#include "Core.hpp"
#include "KeyCodes.hpp"
#include "MouseCodes.hpp"

#include <utility>

namespace Silfur
{
        class Input
        {
            public:
            static bool IsKeyPressed(KeyCode key);

            static bool IsMouseButtonPressed(MouseCode button);
            static std::pair<float, float> GetMousePosition();
            static float GetMouseX();
            static float GetMouseY();
        };
}

#endif // __SILFUR_CORE_INPUT_HPP__
