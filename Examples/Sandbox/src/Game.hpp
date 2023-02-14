#pragma once

#include <Silfur.hpp>

class Game : public Silfur::Application
{
public:
    Game(int argc, char** argv, const std::string& appName, const Silfur::Version appVersion);

    virtual void OnInitialize() override;
    virtual void OnUpdate(float ts) override;

    bool PrintMouseButtonDownInfos(Silfur::Event& p_event);
};
