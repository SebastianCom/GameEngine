#pragma once

class Game;
class PlayerController;

class ThirdPersonScene : public fw::Scene
{
public:
    ThirdPersonScene(Game* pGame);
    virtual ~ThirdPersonScene();

    virtual void StartFrame(float deltaTime) override;
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;

protected:
    PlayerController* m_pPlayerController = nullptr;
};
