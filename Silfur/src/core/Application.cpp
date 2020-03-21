#include "sfpch.h"
#include "Application.h"

#include "utility/log/Log.h"

#include <wrl.h>
#include <dxgi1_6.h>

using namespace Microsoft::WRL;

namespace Silfur
{
    Application::Application()
    {
        Log::Init();
        CheckTearingSupport();
    }

    Application::~Application()
    {
    }

    void Application::CreateWindow(VideoMode p_mode, const wchar_t* p_title)
    {
        m_Window = CreateScope<Window>(p_mode, p_title);
    }

    bool Application::Run()
    {
        m_Window->ProcessEvents();

        if (m_Window->IsClosed)
        {
            return false;
        }

        return true;
    }

    void* Application::GetSystemWindowHandle()
    {
        return m_Window->HWnd;
    }

    void Application::CheckTearingSupport()
    {
        BOOL allowTearing = FALSE;

        // Rather than create the DXGI 1.5 factory interface directly, we create the
        // DXGI 1.4 interface and query for the 1.5 interface. This is to enable the
        // graphics debugging tools which will not support the 1.5 factory interface
        // until a future update.
        ComPtr<IDXGIFactory4> factory4;
        if (SUCCEEDED(::CreateDXGIFactory1(IID_PPV_ARGS(&factory4))))
        {
            ComPtr<IDXGIFactory5> factory5;
            if (SUCCEEDED(factory4.As(&factory5)))
            {
                if (FAILED(factory5->CheckFeatureSupport(
                    DXGI_FEATURE_PRESENT_ALLOW_TEARING,
                    &allowTearing, sizeof(allowTearing))))
                {
                    allowTearing = FALSE;
                }
            }
        }

        TearingSupported = (allowTearing == TRUE);
    }

}
