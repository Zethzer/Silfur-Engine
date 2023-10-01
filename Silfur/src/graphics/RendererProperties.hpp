#pragma once

#include "defines.hpp"

#include "core/window/Window.hpp"

#include <string>

namespace Silfur
{
    struct RendererProperties
    {
        std::string ApplicationName = "";
        Version ApplicationVersion = { 1,0,0 };

        std::string EngineName = "Silfur Engine";
        Version EngineVersion = { 1,0,0 };

#ifdef SF_DEBUG
        const b8 EnableValidationLayers = true;
#else
        const b8 EnableValidationLayers = false;
#endif
    };
}
