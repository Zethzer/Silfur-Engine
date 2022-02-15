#pragma once

namespace Silfur
{
    enum class EventType
    {
        None = 0,
        KeyPressed, KeyReleased,
        MouseButtonDown, MouseButtonUp, MouseMotion, MouseWheel,
        WindowClose, WindowMoved, WindowSizeChanged, WindowResized,
        WindowEnter, WindowLeave, WindowFocusGained, WindowFocusLost
    };
}
