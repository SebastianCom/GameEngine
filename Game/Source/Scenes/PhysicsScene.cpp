#include "Framework.h"

#include "PhysicsScene.h"
#include "DataTypes.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/Player.h"
#include "Game.h"

PhysicsScene::PhysicsScene(Game* pGame)
    : fw::Scene( pGame )
{
    m_pPhysicsWorld = new fw::PhysicsWorldBox2D( pGame->GetFramework()->GetEventManager() );
    m_pPhysicsWorld->SetGravity( vec3( 0, -10, 0 ) );

    m_pCamera = new fw::Camera( this, vec3(2, 0, -15) );
    m_pCamera->SetLookAtPosition( vec3(2, 0, 0) );

    m_pPlayerController = new PlayerController( pGame->GetFramework()->GetEventManager() );

    // BG
    fw::GameObject* pBG = new fw::GameObject( "Ground", this, vec3(0,0,10) );
    pBG->AddComponent( new fw::MeshComponent( pGame->GetMesh("Sprite"), pGame->GetMaterial("BG") ) );
    pBG->GetTransform()->SetScale( vec3( 5, 5, 1 ) );
    m_Objects.push_back( pBG );

    // Player.
    Player* pPlayer = new Player( this, vec3(2,5,0), m_pPlayerController );
    pPlayer->AddComponent( new fw::MeshComponent( pGame->GetMesh("Sprite"), pGame->GetMaterial("Sprites") ) );
    pPlayer->SetSpriteSheet( pGame->GetSpriteSheet("Sprites") );
    pPlayer->CreateBody( m_pPhysicsWorld, true, 1 );
    //m_pPhysicsWorld->CreateJoint( pPlayer->GetPhysicsBody(), vec3(0,5,0) );
    m_Objects.push_back( pPlayer );

    // Ground Object.
    fw::GameObject* pGameObject = new fw::GameObject( "Ground", this, vec3(0,-5,0) );
    pGameObject->AddComponent( new fw::MeshComponent( pGame->GetMesh("Sprite"), pGame->GetMaterial("Sprites") ) );
    pGameObject->GetTransform()->SetScale( vec3( 5, 2, 1 ) );
    pGameObject->CreateBody( m_pPhysicsWorld, false, 1 );
    m_Objects.push_back( pGameObject );

    //m_pCamera->SetObjectWeAreLookingAt( pPlayer );
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
    fw::Scene::OnEvent( pEvent );
}

void PhysicsScene::Update(float deltaTime)
{
    Scene::Update( deltaTime );

    float time = (float)fw::GetSystemTimeSinceGameStart() * 20;
    //m_Objects[0]->SetRotation( vec3( 0, time, 0 ) );

    // Ask componentmanager for all player components.
    // loop over them and update them.
}
