#include "Framework.h"

#include "ThirdPersonScene.h"
#include "DataTypes.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/Player.h"
#include "Game.h"

ThirdPersonScene::ThirdPersonScene(Game* pGame)
    : fw::Scene( pGame )
{
    m_pPlayerController = new PlayerController( pGame->GetFramework()->GetEventManager() );

    m_pCamera = new fw::Camera( this, vec3(0, 28, -80) );

    // Ground Object.
    fw::GameObject* pGameObject = new fw::GameObject( "Cube", this, vec3(0,-0.05f,0) );
    pGameObject->GetTransform()->SetScale( vec3(30.0f,0.1f,30.0f) );
    pGameObject->AddComponent( new fw::MeshComponent( pGame->GetMesh("Cube"), pGame->GetMaterial("BG") ) );
    m_Objects.push_back( pGameObject );

    // Random Cube Object.
    pGameObject = new fw::GameObject( "Cube", this, vec3(0,2,0) );
    pGameObject->GetTransform()->SetScale( vec3(2) );
    pGameObject->AddComponent( new fw::MeshComponent( pGame->GetMesh("Cube"), pGame->GetMaterial("Water") ) );
    m_Objects.push_back( pGameObject );

    // Random Cube Object.
    pGameObject = new fw::GameObject( "Cube", this, vec3(-15,1,3) );
    pGameObject->GetTransform()->SetScale( vec3(1) );
    pGameObject->AddComponent( new fw::MeshComponent( pGame->GetMesh("Cube"), pGame->GetMaterial("Water") ) );
    m_Objects.push_back( pGameObject );

    // Random Cube Object.
    pGameObject = new fw::GameObject( "Cube", this, vec3(7,1,-6) );
    pGameObject->GetTransform()->SetScale( vec3(1) );
    pGameObject->AddComponent( new fw::MeshComponent( pGame->GetMesh("Cube"), pGame->GetMaterial("Water") ) );
    m_Objects.push_back( pGameObject );

    // Player Object.
    Player* pPlayer = new Player(this, vec3(0, 1, -4), m_pPlayerController);
    pPlayer->GetTransform()->SetScale(vec3(1));
    pPlayer->AddComponent(new fw::MeshComponent(pGame->GetMesh("Cube"), pGame->GetMaterial("Sprites")));
    m_Objects.push_back(pPlayer);

    m_pCamera->SetObjectWeAreLookingAt( pPlayer );
}

ThirdPersonScene::~ThirdPersonScene()
{
}

void ThirdPersonScene::StartFrame(float deltaTime)
{
    m_pPlayerController->StartFrame();
}

void ThirdPersonScene::OnEvent(fw::Event* pEvent)
{
    fw::Scene::OnEvent( pEvent );
}

void ThirdPersonScene::Update(float deltaTime)
{
    Scene::Update( deltaTime );

    fw::FWCore* pFramework = static_cast<Game*>(m_pGame)->GetFramework();
    m_pCamera->Hack_ThirdPersonCamUpdate( pFramework, deltaTime );
}
