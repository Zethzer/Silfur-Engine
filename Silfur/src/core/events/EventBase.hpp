#pragma once

#ifndef __SILFUR_CORE_EVENTS_EVENT_BASE_HPP__
#define __SILFUR_CORE_EVENTS_EVENT_BASE_HPP__

#include "EventSystemType.hpp"

namespace Silfur
{
#define EVENT_SYSTEM_CLASS_TYPE(type)  static EventSystemType GetStaticType() { return EventSystemType::type; }\
                                virtual EventSystemType GetEventType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #type; }

    class SystemEvent
    {
    public:
        SystemEvent() = default;
        virtual ~SystemEvent() = default;

        inline virtual EventSystemType GetEventType() const { return EventSystemType::None; }
        inline virtual const char* GetName() const { return "None"; }
        virtual std::string ToString() const { return GetName(); }
        virtual UniqueRef<SystemEvent> Clone() = 0;
    };

#define EVENT_GAME_CLASS_TYPE(type) virtual std::string GetEventType() const override { return #type; }

    class GameEvent
    {
    public:
        GameEvent() = default;
        virtual ~GameEvent() = default;

        inline virtual std::string GetName() const { return "None"; }
        virtual std::string ToString() const { return GetName(); }
        virtual UniqueRef<GameEvent> Clone() = 0;
    };
}

#endif // __SILFUR_CORE_EVENTS_EVENT_BASE_HPP__
