#include "Framework.h"

#include "Assignment1Scene.h"
#include "DataTypes.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/Player.h"
#include "Game.h"
#include "Components/MeshComponent.h"



Assignment1Scene::Assignment1Scene(Game* pGame)
    :fw::Scene( pGame )
{

    m_pPhysicsWorld = new fw::PhysicsWorldBox2D(pGame->GetFrameWork()->GetEventManager());
    m_pPhysicsWorld->SetGravity(vec2(0, -10));
    m_pCamera = new fw::Camera(this, vec3(0, 0, -20), vec3(0,0,0), 45.0f); 
    m_pPlayerController = new PlayerController();



    Player* pPlayer = new Player(this,vec2(0, 0), m_pPlayerController);
    
    //Change to ewe
    pPlayer->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("Ewe")));
    pPlayer->CreateBody(m_pPhysicsWorld, true, vec2(1, 1), 1);
    
    m_ActiveObjects.push_back(pPlayer);
    
    //Change to ground
    fw::GameObject* pGround = new fw::GameObject(this, vec2(0, -6));
    pGround->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("Ground")));
    pGround->CreateBody(m_pPhysicsWorld, true, vec2(8, 1), 0);
    m_ActiveObjects.push_back(pGround);

    fw::GameObject* BackGround = new fw::GameObject(this, vec2(-9, -9));
    BackGround->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("BackGround")));
    BackGround->SetScale(vec2(18, 18));

    bCollision = false;
}

Assignment1Scene::~Assignment1Scene()
{
    delete m_pPlayerController;
}

void Assignment1Scene::StartFrame(float deltaTime)
{
    m_pPlayerController->StartFrame();
}

void Assignment1Scene::OnEvent(fw::Event* pEvent)
{
    m_pPlayerController->OnEvent(pEvent);
    fw::Scene::OnEvent(pEvent);

    if (CollObjectA == m_ActiveObjects[0] || CollObjectA == m_ActiveObjects[1])
    {
        if (CollObjectA == m_ActiveObjects[0] || CollObjectB == m_ActiveObjects[1])
        {
           Player* pPlayer = static_cast<Player*>(m_ActiveObjects[0]);
           if (pPlayer)
           {
               pPlayer->bOnGround = true;
               bCollision = true;
           }
        }

    }
    else
    {
        bCollision = false;
    }
}

void Assignment1Scene::Reset()
{
    //m_ActiveObjects[0]->SetPosition(vec2(0, 5));

}

void Assignment1Scene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
    b2Vec2 Position = vec2(m_ActiveObjects[1]->GetPosition().x, m_ActiveObjects[1]->GetPosition().y);
    b2Vec2 Position2 = vec2(m_ActiveObjects[1]->m_pPhysicsBody->GetBody()->GetPosition().x, m_ActiveObjects[1]->m_pPhysicsBody->GetBody()->GetPosition().y);
    ImGui::Text("%0.2f, %0.2f, %0.2f", Position.x, Position.y, 0);
    ImGui::Text("%0.2f, %0.2f, %0.2f", Position2.x, Position2.y, 0);
    ImGui::Checkbox("Collision", &bCollision);
}