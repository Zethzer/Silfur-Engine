#include <Silfur.hpp>
#include <Core/EntryPoint.hpp>

#include "Game.hpp"

Silfur::Application* Silfur::CreateApplication(Silfur::ApplicationCommandLineArgs commandLineArgs)
{
    Silfur::ApplicationProperties properties;
    properties.Name = "Sandbox App";
    properties.Width = 1024;
    properties.Height = 576;
    properties.Version = { 0, 1, 0 };
    properties.CommandLineArgs = commandLineArgs;

    return new Game(properties);
}