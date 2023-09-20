#include "Game.hpp"

// Listener for example of binding function in global scope
bool PrintMouseWheelInfos(Silfur::Event& event)
{
    // dynamic_cast from a reference can raise bad_cast exception. You can handle this exception
    try
    {
        // For getting the event informations, you need to dynamic_cast the parameter "event" into his derived type
        // For reminder, the derived type is always the same as the type pass when adding the listener
        Silfur::MouseWheelEvent* mouseWheelEvent = dynamic_cast<Silfur::MouseWheelEvent*>(&event);

        SF_TRACE(Temp, "Mouse wheel event informations: {}", mouseWheelEvent->ToString());

        return true;
    }
    catch (std::bad_cast b)
    {
        SF_ERROR(Input, 0, "Impossible to cast Event into MouseWheelEvent : {}", b.what());
        return true;
    }
}

Game::Game(int argc, char** argv, const std::string& appName, const Silfur::Version appVersion)
    : Application(argc, argv, appName, appVersion)
{
    // Add a listener to an event from global function
    GetEventHandler().AddListener<Silfur::MouseWheelEvent>(SF_BIND_FN(PrintMouseWheelInfos));

    // Add a listener to an event from a class member function
    GetEventHandler().AddListener<Silfur::MouseButtonDownEvent>(SF_BIND_MEMBER_FN(PrintMouseButtonDownInfos));
};

void Game::OnInitialize()
{
    SF_TRACE(Init, "Game Initialized!");
}

void Game::OnUpdate(float ts)
{
    // Input polling for keyboard and mouse
    if (Silfur::Input::IsKeyPressed(Silfur::VKey::Escape))
    {
        // Just an example of pushing existing event type
        GetEventHandler().PushEvent(Silfur::CreateScope<Silfur::WindowCloseEvent>(Silfur::WindowCloseEvent()));

        // This line does the same thing
        //Shutdown();
    }
    else if (Silfur::Input::IsKeyPressed(Silfur::ScanCode::A))
    {
        SF_TRACE(Temp, "Key: {}", Silfur::Input::GetKeyName(Silfur::ScanCode::A));
        SF_TRACE(Temp, "Key Scancode: {}", Silfur::Input::GetScanCodeName(Silfur::ScanCode::A));
    }

    if (Silfur::Input::IsMouseButtonPressed(Silfur::MouseButton::Left))
    {
        //SF_TRACE(Temp, "Left button pressed");
    }
    else if (Silfur::Input::IsMouseButtonPressed(Silfur::MouseButton::Right))
    {
        //SF_TRACE(Temp, "Right button pressed");
    }
}

bool Game::PrintMouseButtonDownInfos(Silfur::Event& event)
{
    // It's not mandatory to handle the bad_cast exception. It's your choice

    // You can also use static_cast but it's not safe if you register the method to a listener of a different type of event
    Silfur::MouseButtonDownEvent* mouseButtonDownEvent = static_cast<Silfur::MouseButtonDownEvent*>(&event);
    Silfur::MouseButtonDownInfo mouseButtonDownInfo = mouseButtonDownEvent->GetInfos();
    
    SF_TRACE(Temp, "Mouse button down event button id: {}", static_cast<int>(mouseButtonDownInfo.button));
    
    return true;
}
