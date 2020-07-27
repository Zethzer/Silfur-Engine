#include "sfpch.hpp"
#include "EventManager.hpp"

namespace Silfur
{
    std::vector<Scope<Event>> EventManager::s_Events;
    std::unordered_map<EventType, std::function<void(const Scope<Event>&)>> EventManager::s_Listeners;

    void EventManager::Init()
    {
        s_Events.reserve(10000);
        s_Listeners.reserve(10000);
    }

    void EventManager::PushEvent(Scope<Event> p_event)
    {
        s_Events.push_back(std::move(p_event));
    }

    void EventManager::Dispatch()
    {
        for (const auto& event : s_Events)
        {
            EventType evtType = event->GetEventType();
            std::function<void(const Scope<Event>&)> func = s_Listeners[evtType];
            if (func)
            {
                func(event);
            }
        }

        s_Events.clear();
    }
}
