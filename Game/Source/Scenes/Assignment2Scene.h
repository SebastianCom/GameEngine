#pragma once

class Game;
class PlayerController;

class Assignment2Scene : public fw::Scene
{
public:
    Assignment2Scene(Game* pGame);
    virtual ~Assignment2Scene();

    virtual void StartFrame(float deltaTime) override;
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;

    void HandleCollision();

protected:
    PlayerController* m_pPlayerController = nullptr;

    bool SpinnerToggle = false;

    b2RevoluteJoint* m_pSpinner = nullptr;

    bool m_bCollision = false;
    float m_CollisionTimer = 0.0f;
};
