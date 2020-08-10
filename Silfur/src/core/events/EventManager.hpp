#pragma once

#ifndef __SILFUR_CORE_EVENTS_EVENT_MANAGER_HPP__
#define __SILFUR_CORE_EVENTS_EVENT_MANAGER_HPP__

#include "core/Base.hpp"
#include "EventType.hpp"

#include <vector>
#include <unordered_map>
#include <list>
#include <functional>

#define SF_BIND_FN(fn) [](auto&&... args) -> decltype(auto) \
{ return fn(std::forward<decltype(args)>(args)...); }

#define SF_BIND_MEMBER_FN(fn) [this](auto&&... args) -> decltype(auto) \
{ return this->fn(std::forward<decltype(args)>(args)...); }

namespace Silfur
{
    class Event;

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
            if (s_Listeners[evtType].empty())
            {
                s_Listeners[evtType].resize(5000);
            }
            s_Listeners[evtType].push_back(p_func);
        }

        template<typename EvtT, typename Func>
        static bool RemoveListener(const Func& p_func)
        {
            auto it = std::find_if(s_Listeners.begin(), s_Listeners.end(),
                                   [&p_func](const auto & p) {
                                        for (const auto& func : p.second)
                                        {
                                            return func == p_func;
                                        }
                                    });

            if (it != s_Listeners.end())
            {
                s_Listeners.erase(it);
            }

            return false;
        }

        static void Dispatch();

    private:
        static std::vector<Scope<Event>> s_Events;
        static std::unordered_map<EventType, std::list<std::function<void(Event&)>>> s_Listeners;
    };
}

#endif // __SILFUR_CORE_EVENTS_EVENT_MANAGER_HPP__
