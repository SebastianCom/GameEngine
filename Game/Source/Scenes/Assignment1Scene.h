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

    void SpawnRandomMeteor();


protected:

    PlayerController* m_pPlayerController = nullptr;
    std::vector<fw::GameObject*> m_pMeteors;
    std::vector<fw::GameObject*> m_pMeatBoneChunks;

    fw::Material* m_pMat = nullptr;
    fw::Mesh* m_pMesh = nullptr;

    bool bCollision;
    int NumMeteor = 20;

    //fw::Material* m_Material;

    float SpawnTimer = 2.0f;


};

