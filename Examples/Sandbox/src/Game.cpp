#include <Silfur.hpp>
#include <Core/EntryPoint.hpp>

// Listener for example of binding function in global scope
bool PrintMouseWheelInfos(Silfur::Event& p_event)
{
    SF_TRACE(Temp, "Mouse wheel event informations: {}", p_event.ToString());
    return true;
}

// Class examples
class Game : public Silfur::Application
{
public:
    Game(int argc, char** argv, const std::string& appName, const Silfur::Version appVersion)
        : Application(argc, argv, appName, appVersion)
    {
        // Add a listener to an event from global function
        GetEventHandler().AddListener<Silfur::MouseWheelEvent>(SF_BIND_FN(PrintMouseWheelInfos));

        // Add a listener to an event from a class member function
        GetEventHandler().AddListener<Silfur::MouseButtonDownEvent>(SF_BIND_MEMBER_FN(PrintMouseButtonDownInfos));
    };

    virtual void OnInitialize() override
    {
        SF_TRACE(Init, "Game Initialized!");
    }

    virtual void OnUpdate(float ts) override
    {
        // Input polling for keyboard and mouse
        if (Silfur::Input::IsKeyPressed(Silfur::VKey::Escape))
        {
            // Just an example of pushing existing event type
            GetEventHandler().PushEvent(Silfur::CreateScope<Silfur::WindowCloseEvent>(Silfur::WindowCloseEvent()));

            // This line does the same thing
            //Shutdown();
        }
        else if (Silfur::Input::IsKeyPressed(Silfur::VKey::A))
        {
            SF_TRACE(Temp, "Key: {}", Silfur::Input::GetKeyName(Silfur::VKey::A));
        }

        if (Silfur::Input::IsMouseButtonPressed(Silfur::MouseButton::Left))
        {
            SF_TRACE(Temp, "Left button pressed");
        }
        else if (Silfur::Input::IsMouseButtonPressed(Silfur::MouseButton::Right))
        {
            SF_TRACE(Temp, "Right button pressed");
        }
    }

    bool PrintMouseButtonDownInfos(Silfur::Event& p_event)
    {
        SF_TRACE(Temp, "Mouse button down event informations: {}", p_event.ToString());
        return true;
    }
};

Silfur::Application* Silfur::CreateApplication(int argc, char** argv)
{
    return new Game(argc, argv, "Sandbox App", { 0, 1, 0 });
}

//#if defined(_WIN32) && defined(_MSC_VER) && defined(_NDEBUG)
//int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//#else
//int main(int argc, char** argv)
//#endif
//{
//    Silfur::Application app("Hello Sandbox", { 0, 1, 0 });
//    Silfur::Window& window = app.CreateWindow({ 800, 600 }, "Main Window");
//
//    // Add a listener to an event in global scope, MouseWheelEvent for example
//    window.GetEventHandler().AddListener<Silfur::MouseWheelEvent>(SF_BIND_FN(PrintMouseWheelInfos));
//
//    // Instantiate the class example
//    Game game(window);
//
//    while (app.Run())
//    {
//        // Input polling for keyboard and mouse
//        if (Silfur::Input::IsKeyPressed(Silfur::VKey::Escape))
//        {
//            // Just an example of pushing existing event type
//            window.GetEventHandler().PushEvent(Silfur::CreateScope<Silfur::WindowCloseEvent>(Silfur::WindowCloseEvent()));
//
//            // This line does the same thing
//            //app.Shutdown();
//        }
//        else if (Silfur::Input::IsKeyPressed(Silfur::VKey::A))
//        {
//            SF_TRACE(Temp, "Key: {}", Silfur::Input::GetKeyName(Silfur::VKey::A));
//        }
//
//        if (Silfur::Input::IsMouseButtonPressed(Silfur::MouseButton::Left))
//        {
//            SF_TRACE(Temp, "Left button pressed");
//        }
//        else if (Silfur::Input::IsMouseButtonPressed(Silfur::MouseButton::Right))
//        {
//            SF_TRACE(Temp, "Right button pressed");
//        }
//    }
//
//    return EXIT_SUCCESS;
//}
