#pragma once

class Game;

class CubeScene: public fw::Scene
{
public:
    CubeScene(Game* pGame);
    virtual ~CubeScene();

    virtual void StartFrame(float deltaTime) override;
    virtual void Update(float deltaTime);
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Reset() override {};
    //virtual void Draw();


protected:




};

