#pragma once

#include "defines.hpp"
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
        explicit KeyEvent(KeyInfo keyInfo)
            : m_KeyInfo(keyInfo)
        {}

        virtual Scope<Event> Clone() override
        {
            return CreateScope<KeyEvent>(*this);
        }

        KeyInfo m_KeyInfo;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        explicit KeyPressedEvent(KeyInfo keyInfo)
            : KeyEvent(keyInfo)
        {}

        inline int IsRepeated() { return m_KeyInfo.repeated; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: Key: " << m_KeyInfo.vKey << " | Scancode: "
                << m_KeyInfo.scancode << " (" << m_KeyInfo.repeated << ")";
            return ss.str();
        }

        Scope<Event> Clone() override
        {
            return CreateScope<KeyPressedEvent>(*this);
        }

        EVENT_CLASS_TYPE(KeyPressed)
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        explicit KeyReleasedEvent(KeyInfo keyInfo)
                : KeyEvent(keyInfo)
        {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: Key: " << m_KeyInfo.vKey << " | Scancode: "
               << m_KeyInfo.scancode;
            return ss.str();
        }

        Scope<Event> Clone() override
        {
            return CreateScope<KeyReleasedEvent>(*this);
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}
