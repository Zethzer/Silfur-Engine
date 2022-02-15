#include <Silfur.hpp>

// Listener for example of binding function in global scope
void PrintMouseWheelInfos(Silfur::Event& p_event)
{
    SF_TRACE(Temp, "Mouse wheel event informations: {}", p_event.ToString());
}

// Class example
class Game
{
public:
    Game(const Silfur::Window& p_window)
    {
        // Add a listener to an event in a class, MouseButtonDownEvent for example. You can use 2 ways :
        // Way 1 : By using the const reference of the window
        p_window.GetEventHandler().AddListener<Silfur::MouseButtonDownEvent>(SF_BIND_MEMBER_FN(PrintMouseButtonDownInfos));

        // Way 2 : If you don't want to pass the reference of the window. The application instance is unique and possess the window
        Silfur::Application::Get().GetWindow().GetEventHandler().AddListener<Silfur::MouseButtonDownEvent>(SF_BIND_MEMBER_FN(PrintMessageOnMouseButtonDown));
    };

    void PrintMouseButtonDownInfos(Silfur::Event& p_event)
    {
        SF_TRACE(Temp, "Mouse button down event informations: {}", p_event.ToString());
    }

    void PrintMessageOnMouseButtonDown(Silfur::Event& p_event)
    {
        SF_TRACE(Temp, "Message on mouse button down!");
    }
};

#if defined(_WIN32) && defined(_MSC_VER) && defined(_NDEBUG)
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char** argv)
#endif
{
    Silfur::Application app("Hello Sandbox", { 0, 1, 0 });
    Silfur::Window& window = app.CreateWindow({ 800, 600 }, "Main Window");

    // Add a listener to an event in global scope, MouseWheelEvent for example
    window.GetEventHandler().AddListener<Silfur::MouseWheelEvent>(SF_BIND_FN(PrintMouseWheelInfos));

    // Instantiate the class example
    Game game(window);

    while (app.Run())
    {
        // Input polling for keyboard and mouse
        if (Silfur::Input::IsKeyPressed(Silfur::VKey::Escape))
        {
            // Just an example of pushing existing event type
            window.GetEventHandler().PushEvent(Silfur::CreateScope<Silfur::WindowCloseEvent>(Silfur::WindowCloseEvent()));

            // This line does the same thing
            //app.Shutdown();
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

    return EXIT_SUCCESS;
}
