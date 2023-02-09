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
        static VKey FromSDL(SDL_Keycode keycode);
        static ScanCode FromSDL(SDL_Scancode scancode);
        static MouseButton FromSDL(uint8_t sdlButton);
        static SDL_Keycode ToSDL(VKey keycode);
        static SDL_Scancode ToSDL(ScanCode scancode);
    };
}
