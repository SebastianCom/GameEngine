#pragma once

class PlayerController;
class Game;


class Assignment1Scene: public fw::Scene
{
public:
    Assignment1Scene(Game* pGame);
    virtual ~Assignment1Scene();

    virtual void StartFrame(float deltaTime) override;
    virtual void Update(float deltaTime);
    virtual void OnEvent(fw::Event* pEvent) override;
    //virtual void Draw();

    virtual void Reset() override;


protected:

    PlayerController* m_pPlayerController = nullptr;
    std::vector<fw::GameObject*> m_InactiveObjects;
    std::vector<fw::GameObject*> m_Meteors;
    std::vector<fw::GameObject*> m_MeatBoneChunks;

    bool bCollision;

    //fw::Material* m_Material;


};

