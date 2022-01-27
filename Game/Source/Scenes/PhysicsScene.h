#pragma once

class PlayerController;
class Game;

class PhysicsScene: public fw::Scene
{
public:
    PhysicsScene(Game* pGame);
    virtual ~PhysicsScene();

    virtual void StartFrame(float deltaTime) override;
    //virtual void Update(float deltaTime);
    virtual void OnEvent(fw::Event* pEvent) override;
    //virtual void Draw();


protected:

    PlayerController* m_pPlayerController = nullptr;


};

