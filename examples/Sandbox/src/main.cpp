#include <Silfur.hpp>
#include <iostream>

#if defined(_WIN32) && defined(_MSC_VER) && defined(_NDEBUG)
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char** argv)
#endif
{
    Silfur::Application app("Hello Sandbox", {0, 1, 0});
    app.CreateWindow({800, 600}, u8"Main Window");

    while (app.Run())
    {
        // For input polling, the keyboard is consider in US layout : QWERTY
        // Example : SF_KEY_Q is physical Q key on QWERTY keyboard and physical A key on AZERTY keyboard
        if (Silfur::Input::IsKeyPressed(SF_KEY_ESCAPE))
        {
            app.Shutdown();
        }
        // Physical key A on QWERTY keyboard
        else if (Silfur::Input::IsKeyPressed(SF_KEY_A))
        {
            // Will display : 'q' on AZERTY keyboard and 'a' on QWERTY keyboard
            SF_TRACE(Temp, "Key: {}", Silfur::Input::GetKeyName(SF_KEY_A));
        }
    }

    return EXIT_SUCCESS;
}
