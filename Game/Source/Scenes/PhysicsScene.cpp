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
    fw::GameObject* pBG = new fw::GameObject( "BackGround", this, vec3(0,0,10) );
    pBG->AddComponent( new fw::MeshComponent( pGame->GetMesh("Sprite"), pGame->GetMaterial("BG") ) );
    pBG->GetTransform()->SetScale( vec3( 5, 5, 1 ) );
    m_Objects.push_back( pBG );

    //New Player
    fw::GameObject* pPlayer = new fw::GameObject("Player", this, vec3(2, 5, 0));
    pPlayer->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("BG")));
    pPlayer->AddComponent(new fw::PlayerMovementComponent(m_pPlayerController, pPlayer));
    pPlayer->CreateBody(m_pPhysicsWorld, true, 1);
    m_Objects.push_back( pPlayer );

    // Ground Object.
    fw::GameObject* pGameObject = new fw::GameObject( "Ground", this, vec3(0,-5,0) );
    pGameObject->AddComponent( new fw::MeshComponent( pGame->GetMesh("Sprite"), pGame->GetMaterial("Sprites") ) );
    pGameObject->GetTransform()->SetScale( vec3( 5, 2, 1 ) );
    pGameObject->CreateBody( m_pPhysicsWorld, false, 1 );
    m_Objects.push_back( pGameObject );

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

    //TODO
    // Should be this
    //std::vector<fw::Component*>& list = m_pComponentManager->GetComponentsOfType(PlayerMovementComponent::GetStaticType());
    //for (fw::Component* pComponent : list)
    //{
    //    PlayerMovementComponent* pMovementComponent = static_cast<PlayerMovementComponent*>(pComponent);
    //    pMovementComponent->Update(deltaTime);
    //}
    fw::Component* pComponent = m_pComponentManager->GetComponentOftype(fw::PlayerMovementComponent::GetStaticType());
    
    //TODO
    //MOVE into playermovementcomponent 
    fw::PlayerMovementComponent* pPlayerComp = static_cast<fw::PlayerMovementComponent*>(pComponent);
    pPlayerComp->Update(deltaTime);

    

}
