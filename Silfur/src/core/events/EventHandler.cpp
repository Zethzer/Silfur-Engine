#include "sfpch.hpp"
#include "EventHandler.hpp"

namespace Silfur
{
    EventHandler::EventHandler()
    {
        m_Events.reserve(1000);
        m_Listeners.reserve(100);
    }

    void EventHandler::PushEvent(Scope<Event> event)
    {
        m_Events.push_back(std::move(event));
    }

    void EventHandler::Dispatch()
    {
        for (const auto& event : m_Events)
        {
            EventType evtType = event->GetEventType();
            for (const auto& func : m_Listeners[evtType])
            {
                if (func && !event->Handled)
                {
                    event->Handled = func(*event);
                }
            }
        }

        m_Events.clear();
    }
}
