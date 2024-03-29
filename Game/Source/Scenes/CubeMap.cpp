#include "Framework.h"

#include "CubeMap.h"
#include "DataTypes.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/Player.h"
#include "Game.h"
#include "Meshes/Shapes.h"

CubemapScene::CubemapScene(Game* pGame)
    : fw::Scene( pGame )
{
    m_pPlayerController = new PlayerController( pGame->GetFramework()->GetEventManager() );

    m_pCamera = new fw::Camera( this, vec3(0, 28, -80) );

    //// Ground Object.
    //fw::GameObject* pGameObject = new fw::GameObject( "Ground", this, vec3(0,-0.05f,0) );
    //pGameObject->GetTransform()->SetScale( vec3(30.0f,0.1f,30.0f) );
    //pGameObject->AddComponent( new fw::MeshComponent( pGame->GetMesh("Obj"), pGame->GetMaterial("LightBlue") ) );
    //m_Objects.push_back( pGameObject );

    // Player Object.
    fw::GameObject* pPlayer = new fw::GameObject("Player", this, vec3(0, 1, -4));
    pPlayer->GetTransform()->SetScale(vec3(1));
    pPlayer->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sphere"), pGame->GetMaterial("Reflection")));
    pPlayer->AddComponent(new fw::PlayerMovementComponent(m_pPlayerController, pPlayer));
    m_Objects.push_back(pPlayer);


    m_pCamera->SetObjectWeAreLookingAt( pPlayer );
}

CubemapScene::~CubemapScene()
{
}

void CubemapScene::StartFrame(float deltaTime)
{
    m_pPlayerController->StartFrame();
}

void CubemapScene::OnEvent(fw::Event* pEvent)
{
    fw::Scene::OnEvent( pEvent );
}

void CubemapScene::Update(float deltaTime)
{
    Scene::Update( deltaTime );

    fw::FWCore* pFramework = static_cast<Game*>(m_pGame)->GetFramework();
    m_pCamera->Hack_ThirdPersonCamUpdate( pFramework, deltaTime );

    fw::Component* pComponent = m_pComponentManager->GetComponentOftype(fw::PlayerMovementComponent::GetStaticType());
    fw::PlayerMovementComponent* pPlayerComp = static_cast<fw::PlayerMovementComponent*>(pComponent);
    pPlayerComp->Update(deltaTime);

    //float time = (float)fw::GetSystemTimeSinceGameStart() * 20;
    //m_Objects[2]->GetTransform()->SetRotation(vec3(0, time*2, 0));

    
    ImGui::Begin("Camera Debug");
    vec3 pos = m_pCamera->GetTransform()->GetPosition();
    ImGui::Text("Camera Pos: %0.2f, %0.2f, %0.2f", pos.x, pos.y, pos.z);
    ImGui::End();//Camera debug - being undockable was killing me 
}
