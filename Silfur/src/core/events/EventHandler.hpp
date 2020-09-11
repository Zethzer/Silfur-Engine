#pragma once

#ifndef __SILFUR_CORE_EVENTS_EVENT_MANAGER_HPP__
#define __SILFUR_CORE_EVENTS_EVENT_MANAGER_HPP__

#include "core/Base.hpp"
#include "EventBase.hpp"

#include <vector>
#include <unordered_map>
#include <list>
#include <functional>

namespace Silfur
{
    class EventHandler
    {
        using EventsSystemList = std::vector<UniqueRef<SystemEvent>>;
        using EventsGameList = std::vector<UniqueRef<GameEvent>>;
        using SystemListenersMap = std::unordered_map<EventSystemType, std::list<std::function<void(SystemEvent&)>>>;
        using GameListenersMap = std::unordered_map<std::string, std::list<std::function<void(GameEvent&)>>>;

    public:
        EventHandler();
        ~EventHandler() = default;

        EventHandler(const EventHandler&) = delete;
        EventHandler(EventHandler&&) = delete;

        static EventHandler& Get() { return *s_Instance; }

        void PushSystemEvent(UniqueRef<SystemEvent> p_event, bool immediate);
        void PushGameEvent(UniqueRef<GameEvent> p_event, bool immediate);

        template<typename EvtT, typename Func>
        void AddSystemListener(const Func& p_func)
        {
            EventSystemType evtType = EvtT::GetStaticType();
            if (m_SystemListeners[evtType].empty())
            {
                m_SystemListeners[evtType].resize(50);
            }
            
            m_SystemListeners[evtType].push_back(p_func);
        }

        template<typename Func>
        void AddGameListener(std::string p_eventName, const Func& p_func)
        {
            if (m_GameListeners[p_eventName].empty())
            {
                m_GameListeners[p_eventName].resize(50);
            }
            
            m_GameListeners[p_eventName].push_back(p_func);
        }

        template<typename EvtT, typename Func>
        bool RemoveSystemListener(const Func& p_func)
        {
            auto it = std::find_if(m_SystemListeners.begin(), m_SystemListeners.end(),
                                   [&p_func](const auto & p) {
                                        for (const auto& func : p.second)
                                        {
                                            return func == p_func;
                                        }
                                    });

            if (it != m_SystemListeners.end())
            {
                m_SystemListeners.erase(it);
            }

            return false;
        }

        template<typename Func>
        bool RemoveGameListener(const Func& p_func)
        {
            auto it = std::find_if(m_GameListeners.begin(), m_GameListeners.end(),
                [&p_func](const auto& p) {
                for (const auto& func : p.second)
                {
                    return func == p_func;
                }
            });

            if (it != m_GameListeners.end())
            {
                m_GameListeners.erase(it);
            }

            return false;
        }

        void Dispatch();

        EventHandler& operator=(const EventHandler&) = delete;
        EventHandler& operator=(EventHandler&&) = delete;

    private:
        void ProcessSystemEvent(UniqueRef<SystemEvent> p_event);
        void ProcessGameEvent(UniqueRef<GameEvent> p_event);

    private:
        static EventHandler* s_Instance;

        EventsSystemList m_SystemEvents {};
        EventsGameList m_GameEvents {};
        SystemListenersMap m_SystemListeners {};
        GameListenersMap m_GameListeners {};
    };
}

#endif // __SILFUR_CORE_EVENTS_EVENT_MANAGER_HPP__
