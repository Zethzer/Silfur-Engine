#pragma once

#ifndef __SILFUR_CORE_EVENTS_EVENT_HPP__
#define __SILFUR_CORE_EVENTS_EVENT_HPP__

namespace Silfur
{
    enum class EventType
    {
        None = 0,
        KeyPressed, KeyReleased, KeyTyped
    };

#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::type; }\
                                virtual EventType GetEventType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #type; }

    class Event
    {
    public:
        Event() = default;
        virtual ~Event() = default;

        inline virtual EventType GetEventType() const { return EventType::None; };
        inline virtual const char* GetName() const { return "None"; };
        virtual std::string ToString() const { return GetName(); };
    };
}

#endif // __SILFUR_CORE_EVENTS_EVENT_HPP__
