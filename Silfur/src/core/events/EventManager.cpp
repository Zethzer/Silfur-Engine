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
        /* TODO Handle the end of events
         * Dispatch is called at every frame so :
         * - Check if the event have to be handled already : add a property in Event
         *  NB : The place in this container is limited. Don't forget to handle that case
         *  - Maybe pop the events once their handle on the frame N+1 ? => Handle on Frame N and delete on Frame N+1
         */
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
