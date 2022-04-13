#pragma once

class Game;
class PlayerController;

class LightScene : public fw::Scene
{
public:
    LightScene(Game* pGame);
    virtual ~LightScene();

    virtual void StartFrame(float deltaTime) override;
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;

protected:
    PlayerController* m_pPlayerController = nullptr;
};
