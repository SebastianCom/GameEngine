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
    void CheckForCollision();
    //virtual void Draw();

    virtual void Reset() override;

    void SpawnRandomMeteor();

    void SpawnMeatChuncks(fw::vec3 Pos);


protected:

    PlayerController* m_pPlayerController = nullptr;
    std::vector<fw::GameObject*> m_pMeteors;
    std::vector<fw::GameObject*> m_pMeatChunks;
    
    fw::MeshComponent* m_pMeteorMeshComp = nullptr;
    fw::MeshComponent* m_pEweMeshComp = nullptr;
    fw::MeshComponent* m_pChunksMeshComp = nullptr;
    fw::MeshComponent* m_pTitleMeshComp = nullptr;
    fw::MeshComponent* m_pEndMeshComp = nullptr;
    fw::MeshComponent* m_pWinMeshComp = nullptr;
    fw::MeshComponent* m_pCurrentTitleMesh = nullptr;

    fw::Material* m_pMeteorMat = nullptr;
    fw::Mesh* m_pMeteorMesh = nullptr;

    fw::Material* m_pMeatMat = nullptr;
    fw::Material* m_pBoneMat = nullptr;
    fw::Mesh* m_pChunkMesh = nullptr;


    bool bCollision;
    int NumMeteor = 20;
    int NumChunks = 10;

    fw::Material* m_Material;

    bool ShakeCam = false;
    bool PlayerCompRemoved = false;
    bool MeatCompRemoved = false;
    bool GameStarted = false;

    float SpawnTimer = 2.0f;

    void ResetButton();


};

