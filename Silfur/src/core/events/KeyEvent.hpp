#pragma once

#ifndef __SILFUR_CORE_EVENTS_KEY_EVENT_HPP__
#define __SILFUR_CORE_EVENTS_KEY_EVENT_HPP__

#include "Event.hpp"
#include "core/Input/KeyCodes.hpp"
#include "utility/StringUtils.hpp"

namespace Silfur
{
    class KeyEvent : public Event
    {
    public:
        inline KeyCode GetKeyCode() const { return m_KeyCode; }

    protected:
        explicit KeyEvent(KeyCode p_keyCode)
            : m_KeyCode(p_keyCode)
        {}

        KeyCode m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        explicit KeyPressedEvent(KeyCode p_keyCode, int p_repeatCount)
            : KeyEvent(p_keyCode), m_RepeatCount(p_repeatCount)
        {}

        inline int GetRepeatCount() { return m_RepeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        int m_RepeatCount;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        explicit KeyReleasedEvent(KeyCode p_keyCode)
                : KeyEvent(p_keyCode)
        {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent
    {
    public:
        explicit KeyTypedEvent(unsigned int p_codePoint)
                : KeyEvent(static_cast<KeyCode>(p_codePoint)), m_CodePoint(p_codePoint)
        {}

        std::string ToString() const override
        {
            return ToUtf8(m_CodePoint);
        }

        EVENT_CLASS_TYPE(KeyTyped)

    private:
        unsigned int m_CodePoint;
    };
}

#endif // __SILFUR_CORE_EVENTS_KEY_EVENT_HPP__
