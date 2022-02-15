#pragma once

#include "Keyboard.hpp"
#include "Mouse.hpp"

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_mouse.h>

namespace Silfur
{
    class SDLHelper
    {
    public:
        static VKey FromSDL(SDL_Keycode p_keycode);
        static ScanCode FromSDL(SDL_Scancode p_scancode);
        static MouseButton FromSDL(uint8_t p_sdlButton);
        static SDL_Keycode ToSDL(VKey p_keycode);
        static SDL_Scancode ToSDL(ScanCode p_scancode);
    };
}
