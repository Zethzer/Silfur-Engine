#include <Silfur.hpp>
#include <stdio.h>

int main(void)
{
    auto window = Silfur::Window::Create("Silfur Engine", 1280, 720);

    bool isRunning = true;
    while (isRunning)
    {
        window->Update();

        if (window->Closed())
        {
            isRunning = false;
        }
    }
}
