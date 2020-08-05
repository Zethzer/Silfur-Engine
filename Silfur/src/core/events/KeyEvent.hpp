#pragma once

#ifndef __SILFUR_CORE_EVENTS_KEY_EVENT_HPP__
#define __SILFUR_CORE_EVENTS_KEY_EVENT_HPP__

#include "Event.hpp"
#include "core/input/Keyboard.hpp"

namespace Silfur
{
    typedef struct KeyInfo
    {
        VKey vKey;
        ScanCode scancode;
        bool alt;
        bool shift;
        bool control;
        bool repeated;
        bool system;
    } KeyInfo;

    class KeyEvent : public Event
    {
    public:
        inline KeyInfo GetInfos() const { return m_KeyInfo; }

    protected:
        explicit KeyEvent(KeyInfo p_keyInfo)
            : m_KeyInfo(p_keyInfo)
        {}

        KeyInfo m_KeyInfo;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        explicit KeyPressedEvent(KeyInfo p_keyInfo)
            : KeyEvent(p_keyInfo)
        {}

        inline int IsRepeated() { return m_KeyInfo.repeated; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: Key: " << m_KeyInfo.vKey << " | Scancode: "
                << m_KeyInfo.scancode << " (" << m_KeyInfo.repeated << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        explicit KeyReleasedEvent(KeyInfo p_keyInfo)
                : KeyEvent(p_keyInfo)
        {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: Key: " << m_KeyInfo.vKey << " | Scancode: "
               << m_KeyInfo.scancode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}

#endif // __SILFUR_CORE_EVENTS_KEY_EVENT_HPP__
