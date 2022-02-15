#pragma once

#include "defines.hpp"
#include "Event.hpp"

#include <vector>
#include <unordered_map>
#include <list>
#include <functional>

namespace Silfur
{
    class EventHandler
    {
        using EventsList = std::vector<Scope<Event>>;
        using ListenersMap = std::unordered_map<EventType, std::list<std::function<void(Event&)>>>;

    public:
        EventHandler();

        EventHandler(const EventHandler&) = delete;
        EventHandler(EventHandler&&) = delete;

        void PushEvent(Scope<Event> p_event);

        template<typename EvtT, typename Func>
        void AddListener(const Func& p_func)
        {
            EventType evtType = EvtT::GetStaticType();
            if (m_Listeners[evtType].empty())
            {
                m_Listeners[evtType].resize(50);
            }
            m_Listeners[evtType].push_back(p_func);
        }

        template<typename EvtT, typename Func>
        bool RemoveListener(const Func& p_func)
        {
            auto it = std::find_if(m_Listeners.begin(), m_Listeners.end(),
                                   [&p_func](const auto & p) {
                                        for (const auto& func : p.second)
                                        {
                                            return func == p_func;
                                        }
                                    });

            if (it != m_Listeners.end())
            {
                m_Listeners.erase(it);
            }

            return false;
        }

        void Dispatch();

        EventHandler& operator=(const EventHandler&) = delete;
        EventHandler& operator=(EventHandler&&) = delete;
    private:
        EventsList m_Events {};
        ListenersMap m_Listeners {};
    };
}
