#include <Silfur.hpp>

// Listener for example of binding function in global scope
void PrintMouseWheelInfos(Silfur::SystemEvent& p_event)
{
    SF_TRACE(Temp, "Mouse wheel event informations: {}", p_event.ToString());
}

// Class example
class Game
{
public:
    Game()
    {
        // Add a listener to an event in a class, MouseButtonDownEvent for example. You can use 2 ways :
        // Way 1 : By using the const reference of the window
        Silfur::EventHandler::Get().AddSystemListener<Silfur::MouseButtonDownEvent>(SF_BIND_MEMBER_FN(PrintMouseButtonDownInfos));

        // Way 2 : If you don't want to pass the reference of the window. The application instance is unique and possess the window
        Silfur::EventHandler::Get().AddSystemListener<Silfur::MouseButtonDownEvent>(SF_BIND_MEMBER_FN(PrintMessageOnMouseButtonDown));
    };

    void PrintMouseButtonDownInfos(Silfur::SystemEvent& p_event)
    {
        SF_TRACE(Temp, "Mouse button down event informations: {}", p_event.ToString());
    }

    void PrintMessageOnMouseButtonDown(Silfur::SystemEvent& p_event)
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
    Silfur::Version appVersion = { 0, 1, 0 };
    Silfur::UniqueRef<Silfur::Application> app = Silfur::CreateUniqueRef<Silfur::Application>("Hello Sandbox", appVersion);
    Silfur::Window& window = app->CreateWindow({800, 600}, u8"Main Window");

    // Add a listener to an event in global scope, MouseWheelEvent for example
    Silfur::EventHandler::Get().AddSystemListener<Silfur::MouseWheelEvent>(SF_BIND_FN(PrintMouseWheelInfos));

    // Instantiate the class example
    Silfur::UniqueRef<Game> game = Silfur::CreateUniqueRef<Game>();

    while (app->Run())
    {
        // Input polling for keyboard and mouse
        if (Silfur::Input::IsKeyPressed(Silfur::VKey::Escape))
        {
            // Just an example of pushing existing event type
            Silfur::EventHandler::Get().PushSystemEvent(Silfur::CreateUniqueRef<Silfur::WindowCloseEvent>(Silfur::WindowCloseEvent()), true);

            // This line does the same thing
            //app->Shutdown();
        }
        else if (Silfur::Input::IsKeyPressed(Silfur::VKey::A))
        {
            SF_TRACE(Temp, "Key: {}", Silfur::Input::GetKeyName(Silfur::VKey::A));
        }
    }

    return EXIT_SUCCESS;
}
