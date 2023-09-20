#include "sfpch.hpp"
#include "Input.hpp"

#include "core/window/Window.hpp"
#include "core/input/Helper.hpp"

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>

namespace Silfur
{

    bool Input::IsKeyPressed(VKey key)
    {
        return IsKeyPressed(ToScanCode(key));
    }

    bool Input::IsKeyPressed(ScanCode scancode)
    {
        return SDL_GetKeyboardState(nullptr)[SDLHelper::ToSDL(scancode)];
    }

    std::string Input::GetKeyName(VKey key)
    {
        SDL_Keycode sdlKey = SDLHelper::ToSDL(key);

        std::string name;
        if (sdlKey != SDLK_UNKNOWN)
        {
            name = SDL_GetKeyName(sdlKey);
        }

        return name.empty()? "Unknow" : name;
    }

    std::string Input::GetKeyName(ScanCode scancode)
    {
        SDL_Scancode sdlScancode = SDLHelper::ToSDL(scancode);

        std::string name;
        if (sdlScancode != SDL_SCANCODE_UNKNOWN)
        {
            SDL_Keycode sdlKey = SDL_GetKeyFromScancode(sdlScancode);
            name = SDL_GetKeyName(sdlKey);
        }

        return name.empty()? "Unknow" : name;
    }

    std::string Input::GetScanCodeName(ScanCode scancode)
    {
        SDL_Scancode sdlScancode = SDLHelper::ToSDL(scancode);

        std::string name;
        if (sdlScancode != SDL_SCANCODE_UNKNOWN)
        {
            name = SDL_GetScancodeName(sdlScancode);
        }

        return name.empty() ? "Unknow" : name;
    }

    ScanCode Input::ToScanCode(VKey key)
    {
        return SDLHelper::FromSDL(SDL_GetScancodeFromKey(SDLHelper::ToSDL(key)));
    }

    VKey Input::ToVirtualKey(ScanCode scancode)
    {
        return SDLHelper::FromSDL(SDL_GetKeyFromScancode(SDLHelper::ToSDL(scancode)));
    }

    bool Input::IsMouseButtonPressed(MouseButton button)
    {
        static int SfMouseButtonToSDLButton[static_cast<size_t>(MouseButton::Max) + 1] = {
            SDL_BUTTON_LMASK,
            SDL_BUTTON_RMASK,
            SDL_BUTTON_MMASK,
            SDL_BUTTON_X1MASK,
            SDL_BUTTON_X2MASK
        };

        return (SDL_GetMouseState(nullptr, nullptr) & SfMouseButtonToSDLButton[static_cast<size_t>(button)]) != 0;
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

    bool Input::SetRelativeMouseMode(bool enabled)
    {
        return SDL_SetRelativeMouseMode((enabled)? SDL_TRUE : SDL_FALSE) == 0;
    }
}
