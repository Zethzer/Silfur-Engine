#pragma once

#include "defines.hpp"
#include "window/Window.hpp"
#include "graphics/vulkan/RendererVk.hpp"

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

    struct ApplicationCommandLineArgs
    {
        int Count = 0;
        char** Args = nullptr;

        const char* operator[](int index) const
        {
            return Args[index];
        }
    };

    struct ApplicationProperties
    {
        std::string Name = "Hello Silfur";
        int Width = 1024;
        int Height = 768;
        Version Version;
        ApplicationCommandLineArgs CommandLineArgs;
    };

    class Application
    {
    public:
        Application() = delete;
        Application(ApplicationProperties properties);
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
        void Create(ApplicationProperties properties);
        void Run();

    private:
        ApplicationProperties m_Properties;
        Scope<Window> m_Window = nullptr;
        Scope<RendererVk> m_Renderer = nullptr;
        float m_LastFrameTime {};

    private:
        static Application* s_Instance;
        #if defined(_WIN32) && defined(_MSC_VER) && defined(_NDEBUG)
            friend int CALLBACK ::WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
        #else
            friend int ::main(int argc, char** argv);
        #endif
    };

    // To be defined in CLIENT
    Application* CreateApplication(ApplicationCommandLineArgs commandLineArgs);
}
