#include "sfpch.h"
#include "Window.h"

#include "core/Core.h"
#include "utility/log/Log.h"

// For function std::max
#include <algorithm>

namespace Silfur
{
    Window::Window(VideoMode p_mode, const wchar_t* p_title) :
        HWnd(nullptr),
        IsClosed(true)
    {
        Create(p_mode, p_title);
    }

    void Window::ProcessEvents()
    {
        MSG msg = {};
        if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT)
            Shutdown();
    }

    void Window::Create(VideoMode p_mode, const wchar_t* p_title)
    {
        int screenWidth = ::GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = ::GetSystemMetrics(SM_CYSCREEN);

        RECT windowRect = { 0, 0, static_cast<LONG>(p_mode.Width), static_cast<LONG>(p_mode.Height) };
        ::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

        int windowWidth = windowRect.right - windowRect.left;
        int windowHeight = windowRect.bottom - windowRect.top;

        // Center the window within the screen. Clamp to 0, 0 for the top-left corner.
        int windowX = std::max<int>(0, (screenWidth - windowWidth) / 2);
        int windowY = std::max<int>(0, (screenHeight - windowHeight) / 2);

        WNDCLASSEXW windowClass{};

        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.style = CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc = &HandleMessages;
        windowClass.cbClsExtra = 0;
        windowClass.cbWndExtra = 0;
        windowClass.hInstance = ::GetModuleHandle(nullptr);
        windowClass.hIcon = ::LoadIcon(windowClass.hInstance, NULL);
        windowClass.hCursor = ::LoadCursor(NULL, IDC_ARROW);
        windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        windowClass.lpszMenuName = NULL;
        windowClass.lpszClassName = L"SilfurMainWindow";
        windowClass.hIconSm = ::LoadIcon(windowClass.hInstance, NULL);

        static ATOM atom = ::RegisterClassExW(&windowClass);
        SF_CORE_ASSERT(atom > 0, "Failed to register Window Class");

        HWND hWnd = ::CreateWindowExW(
            NULL,
            windowClass.lpszClassName,
            p_title,
            WS_OVERLAPPEDWINDOW,
            windowX,
            windowY,
            windowWidth,
            windowHeight,
            NULL,
            NULL,
            windowClass.hInstance,
            this
        );

        SF_CORE_ASSERT(hWnd, "Failed to create window");

        HWnd = hWnd;
        IsClosed = false;

        ::ShowWindow(HWnd, SW_SHOW);
    }

    void Window::Shutdown()
    {
        IsClosed = true;

        ::DestroyWindow(HWnd);
    }

    LRESULT CALLBACK Window::HandleMessages(HWND p_hWnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam)
    {
        Window* windowPtr = nullptr;

        if (p_msg == WM_NCCREATE)
        {
            windowPtr = static_cast<Window*>(reinterpret_cast<CREATESTRUCT*>(p_lParam)->lpCreateParams);

            ::SetLastError(0);
            if (!SetWindowLongPtr(p_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windowPtr)))
            {
                if (GetLastError() != 0)
                    return false;
            }
        }
        else
        {
            windowPtr = reinterpret_cast<Window*>(GetWindowLongPtr(p_hWnd, GWLP_USERDATA));
        }

        if (windowPtr)
        {
            switch (p_msg)
            {
            case WM_SYSKEYDOWN:
            case WM_KEYDOWN:
                {
                    bool alt = (::GetAsyncKeyState(VK_MENU) & 0x8000) != 0;

                    switch (p_wParam)
                    {
                        /*case 'V':
                            g_VSync = !g_VSync;
                            break;*/
                        case VK_ESCAPE:
                            ::PostQuitMessage(0);
                            break;
                        /*case VK_RETURN:
                            if (alt)
                            {
                        case VK_F11:
                            SetFullscreen();
                            }
                            break;*/
                    }
                }
                break;
            // The default window procedure will play a system notification sound 
            // when pressing the Alt+Enter keyboard combination if this message is 
            // not handled.
            case WM_SYSCHAR:
                break;
            case WM_SIZE:
                {
                    RECT clientRect = {};
                    ::GetClientRect(windowPtr->HWnd, &clientRect);

                    int width = clientRect.right - clientRect.left;
                    int height = clientRect.bottom - clientRect.top;

                    //Resize(width, height);
                }
                break;
            case WM_DESTROY:
                ::PostQuitMessage(0);
                break;
            default:
                return ::DefWindowProcW(p_hWnd, p_msg, p_wParam, p_lParam);
            }
        }

        return ::DefWindowProc(p_hWnd, p_msg, p_wParam, p_lParam);
    }
}
