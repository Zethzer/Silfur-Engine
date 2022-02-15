#pragma once

#include "Event.hpp"
#include "core/input/Mouse.hpp"

namespace Silfur
{
    typedef struct MouseButtonUpInfo
    {
        MouseButton button;
        u32 x;  // Relative to window
        u32 y;  // Relative to window
    } MouseButtonUpInfo;

    typedef struct MouseButtonDownInfo
    {
        MouseButton button;
        u32 x;  // Relative to window
        u32 y;  // Relative to window
    } MouseButtonDownInfo;

    typedef struct MouseMotionInfo
    {
        u32 x;  // Relative to window
        u32 y;  // Relative to window
        u32 xRelative;  // Relative motion in the X direction
        u32 yRelative;  // Relative motion in the Y direction
    } MouseMotionInfo;

    typedef struct MouseWheelInfo
    {
        u32 x;  // The amount scrolled horizontally, positive to right and negative to the left
        u32 y;  // The amount scrolled vertically, positive to away from the user and negative towards the user
        u32 direction; // Not consistent across all platform. Multiply by -1 do the trick
    } MouseWheelInfo;

    class MouseButtonDownEvent : public Event
    {
    public:
        explicit MouseButtonDownEvent(MouseButtonDownInfo p_mouseButtonDownInfo)
            : m_MouseButtonDownInfo(p_mouseButtonDownInfo)
        {}

        inline MouseButtonDownInfo GetInfos() const { return m_MouseButtonDownInfo; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonDownEvent: Button: " << m_MouseButtonDownInfo.button
                << " | In position: X: " << m_MouseButtonDownInfo.x << " - Y: " << m_MouseButtonDownInfo.y;
            return ss.str();
        }

        Scope<Event> Clone() override
        {
            return CreateScope<MouseButtonDownEvent>(*this);
        }

        EVENT_CLASS_TYPE(MouseButtonDown)
    private:
        MouseButtonDownInfo m_MouseButtonDownInfo;
    };

    class MouseButtonUpEvent : public Event
    {
    public:
        explicit MouseButtonUpEvent(MouseButtonUpInfo p_mouseButtonUpInfo)
            : m_MouseButtonUpInfo(p_mouseButtonUpInfo)
        {}

        inline MouseButtonUpInfo GetInfos() const { return m_MouseButtonUpInfo; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonUpEvent: Button: " << m_MouseButtonUpInfo.button
               << " | In position: X: " << m_MouseButtonUpInfo.x << " - Y: "
               << m_MouseButtonUpInfo.y;
            return ss.str();
        }

        Scope<Event> Clone() override
        {
            return CreateScope<MouseButtonUpEvent>(*this);
        }

        EVENT_CLASS_TYPE(MouseButtonUp)
    private:
        MouseButtonUpInfo m_MouseButtonUpInfo;
    };

    class MouseMotionEvent : public Event
    {
    public:
        explicit MouseMotionEvent(MouseMotionInfo p_mouseMotionInfo)
            : m_MouseMotionInfo(p_mouseMotionInfo)
        {}

        inline MouseMotionInfo GetInfos() const { return m_MouseMotionInfo; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMotionEvent: In position: X: " << m_MouseMotionInfo.x << " - Y: "
               << m_MouseMotionInfo.y << " || X relative: " << m_MouseMotionInfo.xRelative
               << " - Y relative: " << m_MouseMotionInfo.yRelative;
            return ss.str();
        }

        Scope<Event> Clone() override
        {
            return CreateScope<MouseMotionEvent>(*this);
        }

        EVENT_CLASS_TYPE(MouseMotion)
    private:
        MouseMotionInfo m_MouseMotionInfo;
    };

    class MouseWheelEvent : public Event
    {
    public:
        explicit MouseWheelEvent(MouseWheelInfo p_mouseWheelInfo)
            : m_MouseWheelInfo(p_mouseWheelInfo)
        {}

        inline MouseWheelInfo GetInfos() const { return m_MouseWheelInfo; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseWheelEvent: Amount horizontally: " << m_MouseWheelInfo.x << " - Amount vertically: "
               << m_MouseWheelInfo.y << " || Direction: " << m_MouseWheelInfo.direction;
            return ss.str();
        }

        Scope<Event> Clone() override
        {
            return CreateScope<MouseWheelEvent>(*this);
        }

        EVENT_CLASS_TYPE(MouseWheel)
    private:
        MouseWheelInfo m_MouseWheelInfo;
    };
}
