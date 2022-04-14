#pragma once

class Game;
class PlayerController;

class CubemapScene : public fw::Scene
{
public:
    CubemapScene(Game* pGame);
    virtual ~CubemapScene();

    virtual void StartFrame(float deltaTime) override;
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;

protected:
    PlayerController* m_pPlayerController = nullptr;
};
