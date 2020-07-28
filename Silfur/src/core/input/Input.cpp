#include "sfpch.hpp"
#include "Input.hpp"

#include "core/input/Helper.hpp"

#include <SDL2/SDL_keyboard.h>

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
}
