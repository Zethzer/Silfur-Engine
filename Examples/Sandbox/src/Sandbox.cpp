#include <Silfur.hpp>
#include <Core/EntryPoint.hpp>

#include "Game.hpp"

Silfur::Application* Silfur::CreateApplication(int argc, char** argv)
{
    return new Game(argc, argv, "Sandbox App", 1024, 576, { 0, 1, 0 });
}