#include "sfpch.hpp"
#include "EventHandler.hpp"

namespace Silfur
{
    EventHandler::EventHandler()
    {
        m_SystemEvents.reserve(500);
        m_GameEvents.reserve(500);
        m_SystemListeners.reserve(20);
        m_GameListeners.reserve(100);
    }

    void EventHandler::SetImGUICallback(std::function<bool(SystemEvent&)> p_func)
    {
        m_ImGUICallback = p_func;
    }

    void EventHandler::PushSystemEvent(UniqueRef<SystemEvent> p_event, bool immediate)
    {
        if (immediate)
        {
            ProcessSystemEvent(std::move(p_event));
            return;
        }

        //if (!m_ImGUICallback(*p_event))
        //{
            m_SystemEvents.push_back(std::move(p_event));
        //}
    }

    void EventHandler::PushGameEvent(UniqueRef<GameEvent> p_event, bool immediate)
    {
        if (immediate)
        {
            ProcessGameEvent(std::move(p_event));
            return;
        }

        m_GameEvents.push_back(std::move(p_event));
    }

    void EventHandler::Dispatch()
    {
        for (const auto& event : m_SystemEvents)
        {
            EventSystemType evtType = event->GetEventType();
            for (const auto& func : m_SystemListeners[evtType])
            {
                if (func)
                {
                    func(*event);
                }
            }
        }

        m_SystemEvents.clear();

        for (const auto& event : m_GameEvents)
        {
            std::string nameEvt = event->GetName();
            for (const auto& func : m_GameListeners[nameEvt])
            {
                if (func)
                {
                    func(*event);
                }
            }
        }

        m_GameEvents.clear();
    }

    void EventHandler::ProcessSystemEvent(UniqueRef<SystemEvent> p_event)
    {
        //if (!m_ImGUICallback(*p_event))
        //{
            EventSystemType evtType = p_event->GetEventType();
            for (const auto& func : m_SystemListeners[evtType])
            {
                if (func)
                {
                    func(*p_event);
                }
            }
        //}
    }

    void EventHandler::ProcessGameEvent(UniqueRef<GameEvent> p_event)
    {
        std::string nameEvt = p_event->GetName();
        for (const auto& func : m_GameListeners[nameEvt])
        {
            if (func)
            {
                func(*p_event);
            }
        }
    }
}
