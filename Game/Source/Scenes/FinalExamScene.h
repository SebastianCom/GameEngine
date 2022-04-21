#pragma once

class Game;

enum class RPS
{
    None,
    Rock,
    Paper,
    Sissors
};

class FinalScene : public fw::Scene
{
public:
    FinalScene(Game* pGame);
    virtual ~FinalScene();

    virtual void StartFrame(float deltaTime) override;
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;

protected:

    float m_CountDown = 1.0f;
    float m_Elpased = 0.0f;
    bool Started = false;
    bool Victory = false;
    bool GameEnded = false;
    int Move;

    fw::FWCore* m_pFramework;

    RPS MoveMade = RPS::None;
    RPS AIMade = RPS::None;

    const char* Result = nullptr;

};
