#pragma once

class Game;

class WaterScene: public fw::Scene
{
public:
    WaterScene(Game* pGame);
    virtual ~WaterScene();

    virtual void StartFrame(float deltaTime) override;
    virtual void Update(float deltaTime);
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Reset() override {};
    //virtual void Draw();


protected:



};

