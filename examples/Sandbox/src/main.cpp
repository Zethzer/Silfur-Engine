#include <Silfur.hpp>

// Listener for example of binding function in global scope
void PrintMouseWheelInfos(const Silfur::Scope<Silfur::Event>& p_event)
{
    SF_TRACE(Temp, "Mouse wheel event informations: {}", p_event->ToString());
}

// Class example
class Game
{
public:
    Game()
    {
        // Add a listener to an event in a class, MouseButtonDownEvent for example
        Silfur::EventManager::AddListener<Silfur::MouseButtonDownEvent>(SF_BIND_MEMBER_FN(PrintMouseButtonDownInfos));
        Silfur::EventManager::AddListener<Silfur::MouseButtonDownEvent>(SF_BIND_MEMBER_FN(PrintMessageOnMouseButtonDown));
    };
    ~Game() = default;

    void PrintMouseButtonDownInfos(const Silfur::Scope<Silfur::Event>& p_event)
    {
        SF_TRACE(Temp, "Mouse button down event informations: {}", p_event->ToString());
    }

    void PrintMessageOnMouseButtonDown(const Silfur::Scope<Silfur::Event>& p_event)
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
    Silfur::Application app("Hello Sandbox", {0, 1, 0});
    app.CreateWindow({800, 600}, u8"Main Window");

    // Add a listener to an event in global scope, MouseWheelEvent for example
    Silfur::EventManager::AddListener<Silfur::MouseWheelEvent>(SF_BIND_FN(PrintMouseWheelInfos));

    // Instantiate the class example
    Game game;

    while (app.Run())
    {
        // Input polling for keyboard and mouse
        if (Silfur::Input::IsKeyPressed(Silfur::VKey::Escape))
        {
            app.Shutdown();
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
