#pragma once

#include "core/Window.hpp"

namespace Silfur
{
    class SF_API Win32_Window : public Window
    {
    public:
        Win32_Window() = delete;
        Win32_Window(const std::string& p_title, int p_width, int p_height);

        void Update() override;
        inline bool Closed() const override { return m_IsClosed; }

    protected:
        void Init(const std::string& p_title, int p_width, int p_height) override;
        bool Shutdown() override;

    private:
        static LRESULT CALLBACK s_WndProc(HWND p_hwnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam);

    private:
        HWND m_hwnd;
        bool m_IsClosed;
    };
}
