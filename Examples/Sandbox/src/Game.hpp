#pragma once

#include <Silfur.hpp>

class Game : public Silfur::Application
{
public:
    Game(Silfur::ApplicationProperties properties);

    virtual void OnInitialize() override;
    virtual void OnUpdate(float ts) override;

    bool PrintMouseButtonDownInfos(Silfur::Event& event);
};
