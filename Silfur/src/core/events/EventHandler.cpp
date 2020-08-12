#include "sfpch.hpp"
#include "EventHandler.hpp"

namespace Silfur
{
    EventHandler* EventHandler::s_Instance = nullptr;

    EventHandler::EventHandler()
    {
        s_Instance = this;
        m_Events.reserve(1000);
        m_Listeners.reserve(20);
    }

    EventHandler::EventHandler(const EventHandler& p_other)
    {
        this->m_Events.reserve(p_other.m_Events.size());

        for (const auto& e : p_other.m_Events)
            this->m_Events.push_back(e->Clone());
    }

    void EventHandler::PushEvent(Scope<Event> p_event)
    {
        m_Events.push_back(std::move(p_event));
    }

    void EventHandler::Dispatch()
    {
        for (const auto& event : m_Events)
        {
            EventType evtType = event->GetEventType();
            for (const auto& func : m_Listeners[evtType])
            {
                if (func)
                {
                    func(*event);
                }
            }
        }

        m_Events.clear();
    }
}
