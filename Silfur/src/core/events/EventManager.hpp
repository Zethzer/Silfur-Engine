#pragma once

#ifndef __SILFUR_CORE_EVENTS_EVENT_MANAGER_HPP__
#define __SILFUR_CORE_EVENTS_EVENT_MANAGER_HPP__

#include "core/Core.hpp"
#include "Event.hpp"
#include "KeyEvent.hpp"

#include <vector>
#include <unordered_map>
#include <functional>

#define SF_BIND_FN(fn) [this](auto&&... args) -> decltype(auto) \
{ return this->fn(std::forward<decltype(args)>(args)...); }

namespace Silfur
{
    class EventManager
    {
    public:
        EventManager() = delete;
        EventManager(const EventManager& p_other) = delete;
        EventManager(EventManager&& p_other) = delete;

        static void Init();

        static void PushEvent(Scope<Event> p_event);

        template<typename EvtT, typename Func>
        static void AddListener(const Func& p_func)
        {
            EventType evtType = EvtT::GetStaticType();
            s_Listeners[evtType] = p_func;
        }

        template<typename EvtT, typename Func>
        static bool RemoveListener(const Func& p_func)
        {
            auto it = std::find_if(s_Listeners.begin(), s_Listeners.end(),
                                   [&p_func](const auto & p) { return p.second == p_func; });

            if (it != s_Listeners.end())
            {
                s_Listeners.erase(it);
            }

            return false;
        }

        static void Dispatch();

    private:
        static std::vector<Scope<Event>> s_Events;
        static std::unordered_map<EventType, std::function<void(const Scope<Event>&)>> s_Listeners;
    };
}

#endif // __SILFUR_CORE_EVENTS_EVENT_MANAGER_HPP__
