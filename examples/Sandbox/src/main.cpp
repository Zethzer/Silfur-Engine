#include <Silfur.h>

#if defined(_WIN32) && defined(_MSC_VER) && defined(_NDEBUG)
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char** argv)
#endif
{
    Silfur::Application app;
    
    app.CreateRenderWindow({ 800, 600 }, L"Sandbox");

    while (app.Run())
    {}

    return EXIT_SUCCESS;
}
