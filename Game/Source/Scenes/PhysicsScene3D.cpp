#include "Framework.h"

#include "PhysicsScene3D.h"
#include "DataTypes.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/Player.h"
#include "GameObjects/Player3D.h"
#include "Game.h"

PhysicsScene3D::PhysicsScene3D(Game* pGame) 
	: fw::Scene(pGame)
{
    m_pPhysicsWorld = new fw::PhysicsWorldBullet3D(pGame->GetFramework()->GetEventManager());
    m_pPhysicsWorld->SetGravity(vec3(0, -10, 0));

    m_pCamera = new fw::Camera(this, vec3(2, 0, -15));
    m_pCamera->SetLookAtPosition(vec3(2, 0, 0));

    m_pPlayerController = new PlayerController(pGame->GetFramework()->GetEventManager());

    //// BG
    //fw::GameObject* pBG = new fw::GameObject("Ground", this, vec3(0, 0, 10));
    //pBG->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("BG")));
    //pBG->GetTransform()->SetScale(vec3(5, 5, 1));
    //m_Objects.push_back(pBG);

    // Player.
    Player3D* pPlayer = new Player3D( this, vec3(0.5f,3.5f,0), m_pPlayerController );
    pPlayer->GetTransform()->SetScale( vec3(1) );
    pPlayer->AddComponent( new fw::MeshComponent( pGame->GetMesh("Cube"), pGame->GetMaterial("Sprites") ) );
    pPlayer->CreateBody(m_pPhysicsWorld, true, 1);
    m_Objects.push_back( pPlayer );

    // Ground Object.
    fw::GameObject* pGameObject = new fw::GameObject("Cube", this, vec3(0, -0.05f, 0));
    pGameObject->GetTransform()->SetScale(vec3(30.0f, 0.1f, 30.0f));
    pGameObject->AddComponent(new fw::MeshComponent(pGame->GetMesh("Cube"), pGame->GetMaterial("BG")));
    pGameObject->CreateBody(m_pPhysicsWorld, false, 0);
    m_Objects.push_back(pGameObject);

    // Random Cube Object.
    pGameObject = new fw::GameObject("Cube", this, vec3(0, 2, 0));
    pGameObject->GetTransform()->SetScale(vec3(1));
    pGameObject->AddComponent(new fw::MeshComponent(pGame->GetMesh("Cube"), pGame->GetMaterial("Water")));
    pGameObject->CreateBody(m_pPhysicsWorld, true, 1);
    m_Objects.push_back(pGameObject);

    m_pCamera->SetObjectWeAreLookingAt( pPlayer );
}

PhysicsScene3D::~PhysicsScene3D()
{
    delete m_pPlayerController;
}

void PhysicsScene3D::StartFrame(float deltaTime)
{
    m_pPlayerController->StartFrame();
}

void PhysicsScene3D::OnEvent(fw::Event* pEvent)
{
    fw::Scene::OnEvent(pEvent);
}

void PhysicsScene3D::Update(float deltaTime)
{
    Scene::Update(deltaTime);

    float time = (float)fw::GetSystemTimeSinceGameStart() * 20;
    fw::FWCore* pFramework = static_cast<Game*>(m_pGame)->GetFramework();
    m_pCamera->Hack_ThirdPersonCamUpdate(pFramework, deltaTime);
}
