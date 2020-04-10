#include <Silfur.h>

#include <iostream>

#if defined(_WIN32) && defined(_MSC_VER) && defined(_NDEBUG)
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char** argv)
#endif
{
    Silfur::Application app;

    try
    {
        app.CreateRenderWindow({ 800, 600 }, L"Sandbox");

        while (app.Run())
        {}
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
