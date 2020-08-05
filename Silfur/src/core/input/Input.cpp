#include "sfpch.hpp"
#include "Input.hpp"

#include "core/window/Window.hpp"
#include "core/input/Helper.hpp"

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>

namespace Silfur
{

    bool Input::IsKeyPressed(VKey p_key)
    {
        return IsKeyPressed(ToScanCode(p_key));
    }

    bool Input::IsKeyPressed(ScanCode p_scancode)
    {
        return SDL_GetKeyboardState(nullptr)[SDLHelper::ToSDL(p_scancode)];
    }

    std::string Input::GetKeyName(VKey p_key)
    {
        SDL_Keycode key = SDLHelper::ToSDL(p_key);

        std::string name;
        if (key != SDLK_UNKNOWN)
            name = SDL_GetKeyName(key);

        return name.empty()? u8"Unknow" : name;
    }

    std::string Input::GetKeyName(ScanCode p_scancode)
    {
        SDL_Scancode scancode = SDLHelper::ToSDL(p_scancode);

        std::string name;
        if (scancode != SDL_SCANCODE_UNKNOWN)
            name = SDL_GetScancodeName(scancode);

        return name.empty()? u8"Unknow" : name;
    }

    ScanCode Input::ToScanCode(VKey p_key)
    {
        return SDLHelper::FromSDL(SDL_GetScancodeFromKey(SDLHelper::ToSDL(p_key)));
    }

    VKey Input::ToVirtualKey(ScanCode p_scancode)
    {
        return SDLHelper::FromSDL(SDL_GetKeyFromScancode(SDLHelper::ToSDL(p_scancode)));
    }

    bool Input::IsMouseButtonPressed(MouseButton p_button)
    {
        static int SfMouseButtonToSDLButton[static_cast<size_t>(MouseButton::Max) + 1] = {
            SDL_BUTTON_LMASK,
            SDL_BUTTON_RMASK,
            SDL_BUTTON_MMASK,
            SDL_BUTTON_X1MASK,
            SDL_BUTTON_X2MASK
        };

        return (SDL_GetMouseState(nullptr, nullptr) & SfMouseButtonToSDLButton[static_cast<size_t>(p_button)]) != 0;
    }

    std::pair<int, int> Input::GetMousePosition()
    {
        int x, y;

        SDL_GetGlobalMouseState(&x, &y);

        return std::pair<int, int>(x, y);
    }

    std::pair<int, int> Input::GetMousePositionRelativeToFocusWindow()
    {
        int x, y;

        SDL_GetMouseState(&x, &y);

        return std::pair<int, int>(x, y);
    }

    std::pair<int, int> Input::GetMouseRelativePosition()
    {
        int x, y;

        SDL_GetRelativeMouseState(&x, &y);

        return std::pair<int, int>(x, y);
    }

    bool Input::SetRelativeMouseMode(bool p_enabled)
    {
        return SDL_SetRelativeMouseMode((p_enabled)? SDL_TRUE : SDL_FALSE) == 0;
    }
}
