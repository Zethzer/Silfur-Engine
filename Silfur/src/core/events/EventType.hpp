#pragma once

#ifndef __SILFUR_CORE_EVENTS_EVENT_TYPE_HPP__
#define __SILFUR_CORE_EVENTS_EVENT_TYPE_HPP__

namespace Silfur
{
    enum class EventType
    {
        None = 0,
        KeyPressed, KeyReleased,
        MouseButtonDown, MouseButtonUp, MouseMotion, MouseWheel
    };
}

#endif // __SILFUR_CORE_EVENTS_EVENT_TYPE_HPP__
