#pragma once

#ifndef __SILFUR_CORE_EVENTS_KEY_EVENT_HPP__
#define __SILFUR_CORE_EVENTS_KEY_EVENT_HPP__

#include "Event.hpp"
#include "core/input/Keyboard.hpp"
#include "utility/StringUtils.hpp"

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
        inline VKey GetKeyCode() const { return m_KeyInfo.vKey; }

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

    /*class KeyTypedEvent : public KeyEvent
    {
    public:
        explicit KeyTypedEvent(unsigned int p_codePoint)
                : KeyEvent(static_cast<VKey>(p_codePoint)), m_CodePoint(p_codePoint)
        {}

        std::string ToString() const override
        {
            return ToUtf8(m_CodePoint);
        }

        EVENT_CLASS_TYPE(KeyTyped)

    private:
        unsigned int m_CodePoint;
    };*/
}

#endif // __SILFUR_CORE_EVENTS_KEY_EVENT_HPP__
