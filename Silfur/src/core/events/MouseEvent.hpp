#pragma once

#ifndef __SILFUR_CORE_EVENTS_MOUSE_EVENT_HPP__
#define __SILFUR_CORE_EVENTS_MOUSE_EVENT_HPP__

#include "EventBase.hpp"
#include "core/input/Mouse.hpp"

namespace Silfur
{
    typedef struct MouseButtonUpInfo
    {
        MouseButton button;
        int32_t x;  // Relative to window
        int32_t y;  // Relative to window
    } MouseButtonUpInfo;

    typedef struct MouseButtonDownInfo
    {
        MouseButton button;
        int32_t x;  // Relative to window
        int32_t y;  // Relative to window
    } MouseButtonDownInfo;

    typedef struct MouseMotionInfo
    {
        int32_t x;  // Relative to window
        int32_t y;  // Relative to window
        int32_t xRelative;  // Relative motion in the X direction
        int32_t yRelative;  // Relative motion in the Y direction
    } MouseMotionInfo;

    typedef struct MouseWheelInfo
    {
        int32_t x;  // The amount scrolled horizontally, positive to right and negative to the left
        int32_t y;  // The amount scrolled vertically, positive to away from the user and negative towards the user
        uint32_t direction; // Not consistent across all platform. Multiply by -1 do the trick
    } MouseWheelInfo;

    class MouseButtonDownEvent : public SystemEvent
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

        UniqueRef<SystemEvent> Clone() override
        {
            return CreateUniqueRef<MouseButtonDownEvent>(*this);
        }

        EVENT_SYSTEM_CLASS_TYPE(MouseButtonDown)
    private:
        MouseButtonDownInfo m_MouseButtonDownInfo;
    };

    class MouseButtonUpEvent : public SystemEvent
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

        UniqueRef<SystemEvent> Clone() override
        {
            return CreateUniqueRef<MouseButtonUpEvent>(*this);
        }

        EVENT_SYSTEM_CLASS_TYPE(MouseButtonUp)
    private:
        MouseButtonUpInfo m_MouseButtonUpInfo;
    };

    class MouseMotionEvent : public SystemEvent
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

        UniqueRef<SystemEvent> Clone() override
        {
            return CreateUniqueRef<MouseMotionEvent>(*this);
        }

        EVENT_SYSTEM_CLASS_TYPE(MouseMotion)
    private:
        MouseMotionInfo m_MouseMotionInfo;
    };

    class MouseWheelEvent : public SystemEvent
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

        UniqueRef<SystemEvent> Clone() override
        {
            return CreateUniqueRef<MouseWheelEvent>(*this);
        }

        EVENT_SYSTEM_CLASS_TYPE(MouseWheel)
    private:
        MouseWheelInfo m_MouseWheelInfo;
    };
}

#endif // __SILFUR_CORE_EVENTS_MOUSE_EVENT_HPP__
