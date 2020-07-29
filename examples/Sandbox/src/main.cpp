#include <Silfur.hpp>

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
        if (Silfur::Input::IsKeyPressed(Silfur::VKey::Escape))
        {
            app.Shutdown();
        }
        else if (Silfur::Input::IsKeyPressed(Silfur::VKey::A))
        {
            SF_TRACE(Temp, "Key: {}", Silfur::Input::GetKeyName(Silfur::VKey::A));
        }
    }

    return EXIT_SUCCESS;
}
