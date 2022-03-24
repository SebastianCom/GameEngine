#pragma once

class Game;
class PlayerController;

class PhysicsScene3D : public fw::Scene
{
public:
    PhysicsScene3D(Game* pGame);
    virtual ~PhysicsScene3D();

    virtual void StartFrame(float deltaTime) override;
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    //virtual void Draw() override;

protected:
    PlayerController* m_pPlayerController = nullptr;
};
