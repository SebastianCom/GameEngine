#include "Framework.h"

#include "PhysicsScene.h"
#include "DataTypes.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/Player.h"
#include "Game.h"



PhysicsScene::PhysicsScene(Game* pGame)
    :fw::Scene( pGame )
{
    m_pPhysicsWorld = new fw::PhysicsWorldBox2D();
    //m_pPhysicsWorld->SetGravity(vec2(0, -10));
    m_pPhysicsWorld->SetGravity(vec2(0, 0));


    m_pCamera = new fw::Camera(this, vec2(1.5f * 10, 1.5f * 10) / 2, vec2(1 / 10.0f, 1 / 10.0f));

    m_pPlayerController = new PlayerController();

    //Player* pPlayer = new Player(this, pGame->GetMesh("Sprite"), pGame->GetMaterial("Sokoban"), vec2(7.0f, 9.0f), m_pPlayerController);
    Player* pPlayer = new Player(this, pGame->GetMesh("Cube"), pGame->GetMaterial("Sokoban"), vec2(5.0f, 5.0f), m_pPlayerController);
    pPlayer->SetSpriteSheet(pGame->GetSpriteSheet("Sprites"));
    pPlayer->CreateBody(m_pPhysicsWorld, true, vec2(1, 1), 1);
    m_Objects.push_back(pPlayer);
}

PhysicsScene::~PhysicsScene()
{
    delete m_pPlayerController;
}

void PhysicsScene::StartFrame(float deltaTime)
{
    m_pPlayerController->StartFrame();
}

void PhysicsScene::OnEvent(fw::Event* pEvent)
{
    m_pPlayerController->OnEvent(pEvent);
    fw::Scene::OnEvent(pEvent);
}

void PhysicsScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);

    float time = (float)fw::GetSystemTimeSinceGameStart() * 50;
    m_Objects[0]->SetRotation(vec3(0, time, 0));
}