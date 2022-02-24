#include "Framework.h"

#include "PhysicsScene.h"
#include "DataTypes.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/Player.h"
#include "Game.h"
#include "Components/MeshComponent.h"



PhysicsScene::PhysicsScene(Game* pGame)
    :fw::Scene( pGame )
{
    m_pPhysicsWorld = new fw::PhysicsWorldBox2D(pGame->GetFrameWork()->GetEventManager());
    m_pPhysicsWorld->SetGravity(vec2(0, -10));


    m_pCamera = new fw::Camera(this, vec3(0, 0, -20), vec3(2,5,5), 45.0f); //BROKEN - WORKING ON IT
    m_pPlayerController = new PlayerController();

    Player* pPlayer = new Player(this,vec2(0, 5), m_pPlayerController);
    pPlayer->SetSpriteSheet(pGame->GetSpriteSheet("Sprites"));
    pPlayer->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("Sokoban")));
    pPlayer->CreateBody(m_pPhysicsWorld, true, vec2(1, 1), 1);
    m_ActiveObjects.push_back(pPlayer);
    
    fw::GameObject* pCubeObject = new fw::GameObject("Cube",this, vec2(0.6, 0));
    pCubeObject->AddComponent(new fw::MeshComponent(pGame->GetMesh("Cube"), pGame->GetMaterial("BaseColor")));
    pCubeObject->CreateBody(m_pPhysicsWorld, true, vec2(1, 1), 0);
    m_ActiveObjects.push_back(pCubeObject);
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

void PhysicsScene::Reset()
{
    //m_ActiveObjects[0]->SetPosition(vec2(0, 5));

}

void PhysicsScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
    b2Vec2 Position = vec2(m_ActiveObjects[0]->GetPosition().x, m_ActiveObjects[0]->GetPosition().y);
    ImGui::Text("%0.2f, %0.2f, %0.2f", Position.x, Position.y, 0);

}