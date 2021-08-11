#include "sfpch.hpp"
#include "Win32_Window.hpp"

#include "utils/StringUtils.hpp"

namespace Silfur
{
    Win32_Window::Win32_Window(const std::string& p_title, int p_width, int p_height)
    {
        Init(p_title, p_width, p_height);
    }

    void Win32_Window::Init(const std::string& p_title, int p_width, int p_height)
    {
        int width, height;

        /*
         * When you create a window, the dimensions include the non-client area such as the
         * border and title bar, adjust the window
         */
        RECT windowRect = { 0, 0, static_cast<LONG>(p_width), static_cast<LONG>(p_height) };
        ::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

        width = windowRect.right - windowRect.left;
        height = windowRect.bottom - windowRect.top;

        // Set window's class
        WNDCLASSEX mainWndClass = {};
        mainWndClass.cbSize = sizeof(mainWndClass);
        mainWndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        mainWndClass.lpfnWndProc = s_WndProc;
        mainWndClass.hInstance = ::GetModuleHandle(nullptr);
        mainWndClass.hIcon = ::LoadIcon(nullptr, IDI_APPLICATION);
        mainWndClass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
        mainWndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
        mainWndClass.lpszMenuName = nullptr;
        mainWndClass.lpszClassName = L"MainWndClass";
        mainWndClass.hIconSm = nullptr;

        if (!RegisterClassEx(&mainWndClass))
        {
            // TODO Log error
            return;
        }

        // NOTE (Zeth): On first parameter : WS_EX_ACCEPTFILES : The window accepts drag-drop files.
        if (!(m_hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MainWndClass", StringUtils::s2ws(p_title).c_str(),
            WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, width, height,
            nullptr, nullptr, mainWndClass.hInstance, this)))
        {
            // TODO Log error
            return;
        }

        m_IsClosed = false;
    }

    void Win32_Window::Update()
    {
        MSG msg;

        while (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                Shutdown();
                return;
            }

            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }

        ::UpdateWindow(m_hwnd);

        ::Sleep(0);
    }

    bool Win32_Window::Shutdown()
    {
        m_IsClosed = true;

        return ::DestroyWindow(m_hwnd);
    }

    LRESULT CALLBACK Win32_Window::s_WndProc(HWND p_hwnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam)
    {
        switch (p_msg)
        {
            case WM_KEYDOWN:
                switch (p_wParam)
                {
                    case VK_ESCAPE:
                        ::PostQuitMessage(0);
                    break;
                }
            break;
            case WM_DESTROY:
                ::PostQuitMessage(0);
            break;
            default:
                return ::DefWindowProc(p_hwnd, p_msg, p_wParam, p_lParam);
        }

        return ::DefWindowProc(p_hwnd, p_msg, p_wParam, p_lParam);
    }
}
