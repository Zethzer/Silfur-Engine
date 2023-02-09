#pragma once

#include "defines.hpp"
#include "Version.hpp"
#include "window/Window.hpp"

#if defined(_WIN32)
    #include <Windows.h>
#endif

#if defined(_WIN32) && defined(_MSC_VER) && defined(_NDEBUG)
    int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
#else
    int main(int argc, char** argv);
#endif

namespace Silfur
{
    class Event;

    class Application
    {
    public:
        Application() = delete;
        Application(int argc, char** argv);
        Application(int argc, char** argv, const std::string& appName, const Version& appVersion);
        ~Application();

        Application(const Application&) = delete;
        Application(Application&&) = delete;

        virtual void OnInitialize() {}
        virtual void OnUpdate(float ts) {}

        void Shutdown();

        static Application& Get() { return *s_Instance; }
        inline Window& GetWindow() const { return *m_Window; }
        inline EventHandler& GetEventHandler() const { return m_Window->GetEventHandler(); }
        void* GetSystemWindowHandle();

        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;
    private:
        void Create(int argc, char** argv);
        void Run();

    private:
        Scope<Window> m_Window = nullptr;
        std::string m_AppName{};
        Version m_AppVersion{};
        float m_LastFrameTime = 0.0f;

    private:
        static Application* s_Instance;
        #if defined(_WIN32) && defined(_MSC_VER) && defined(_NDEBUG)
            friend int CALLBACK ::WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
        #else
            friend int ::main(int argc, char** argv);
        #endif
    };

    // To be defined in CLIENT
    Application* CreateApplication(int argc, char** argv);
}
