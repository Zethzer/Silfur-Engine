#pragma once

#include "EventType.hpp"

namespace Silfur
{
#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::type; }\
                                virtual EventType GetEventType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #type; }

    class Event
    {
    public:
        virtual ~Event() = default;

        bool Handled = false;

        inline virtual EventType GetEventType() const { return EventType::None; };
        inline virtual const char* GetName() const { return "None"; };
        virtual std::string ToString() const { return GetName(); };
        virtual Scope<Event> Clone() = 0;
    };
}
