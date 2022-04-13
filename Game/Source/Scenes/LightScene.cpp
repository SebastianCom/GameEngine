#include "Framework.h"

#include "LightScene.h"
#include "DataTypes.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/Player.h"
#include "Game.h"

LightScene::LightScene(Game* pGame)
    : fw::Scene( pGame )
{
    m_pPlayerController = new PlayerController( pGame->GetFramework()->GetEventManager() );

    m_pCamera = new fw::Camera( this, vec3(0, 28, -80) );

    // Ground Object.
    fw::GameObject* pGameObject = new fw::GameObject( "Ground", this, vec3(0,-0.05f,0) );
    pGameObject->GetTransform()->SetScale( vec3(30.0f,0.1f,30.0f) );
    //pGameObject->AddComponent( new fw::LightComponent(vec3(0,2,0), vec3(1,0,0), 5.0f, pGame->GetMesh("Obj")));
    //pGameObject->CreateLight(vec3(0, 2, 0), vec3(1, 0, 0), 5.0f, pGame->GetMesh("Obj"));
    //pGameObject->CreateLight(vec3(6, 2, 0), vec3(0, 1, 0), 5.0f, pGame->GetMesh("Obj"));
    pGameObject->AddComponent( new fw::MeshComponent( pGame->GetMesh("Obj"), pGame->GetMaterial("LitMat") ) );
    m_Objects.push_back( pGameObject );

    //Light Object
    pGameObject = new fw::GameObject("Lights", this, vec3(0, 0, 0));
    pGameObject->CreateLight(vec3(0, 15, 0), vec3(1, 1, 1), 50.0f, pGame->GetMesh("Obj"));
    pGameObject->CreateLight(vec3(10, 1.5f, 0), vec3(0, 1, 0), 30.0f, pGame->GetMesh("Obj"));
    pGameObject->CreateLight(vec3(-10, 1.5f, -5), vec3(1, 0, 0), 30.0f, pGame->GetMesh("Obj"));
    pGameObject->CreateLight(vec3(0, 1.5f, 10), vec3(0, 1, 1), 30.0f, pGame->GetMesh("Obj"));
    m_Objects.push_back(pGameObject);

    // Random Left Wall Object.
    pGameObject = new fw::GameObject( "Left Wall", this, vec3(-15,2,0) );
    pGameObject->GetTransform()->SetScale( vec3(3, 25,25) );
    pGameObject->AddComponent( new fw::MeshComponent( pGame->GetMesh("Cube"), pGame->GetMaterial("LitMat") ) );
    m_Objects.push_back( pGameObject );

    // Random Front Wall Object.
    pGameObject = new fw::GameObject( "Front Wall", this, vec3(0,2,15) );
    pGameObject->GetTransform()->SetScale( vec3(25, 25, 3) );
    pGameObject->AddComponent( new fw::MeshComponent( pGame->GetMesh("Obj"), pGame->GetMaterial("LitMat") ) );
    m_Objects.push_back( pGameObject );

    // Random Right Wall Object.
    pGameObject = new fw::GameObject( "Right Wall", this, vec3(15,2,0) );
    pGameObject->GetTransform()->SetScale( vec3(3, 25, 25) );
    pGameObject->AddComponent( new fw::MeshComponent( pGame->GetMesh("Obj"), pGame->GetMaterial("LitMat") ) );
    m_Objects.push_back( pGameObject );

    // Random Back Wall Object.
    pGameObject = new fw::GameObject("Back Wall", this, vec3(0, 2, -15));
    pGameObject->GetTransform()->SetScale(vec3(25, 25, 3));
    pGameObject->AddComponent(new fw::MeshComponent(pGame->GetMesh("Obj"), pGame->GetMaterial("LitMat")));
    m_Objects.push_back(pGameObject);

    // Player Object.
    fw::GameObject* pPlayer = new fw::GameObject("Sphere", this, vec3(0, 1, 0));
    pPlayer->GetTransform()->SetScale(vec3(1));
    pPlayer->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sphere"), pGame->GetMaterial("LitMat")));
    pPlayer->AddComponent(new fw::PlayerMovementComponent(m_pPlayerController, pPlayer));
    m_Objects.push_back(pPlayer);

    m_pCamera->SetObjectWeAreLookingAt( pPlayer );

    //This could be done easier through the lightcomponent itself, but i am hoping scene managment will load and 
    // unload scenes so that each scene could have 4 lights opposed to the game having a total of 4 lights
    CreateLightComponents();

}

LightScene::~LightScene()
{
}

void LightScene::StartFrame(float deltaTime)
{
    m_pPlayerController->StartFrame();
}

void LightScene::OnEvent(fw::Event* pEvent)
{
    fw::Scene::OnEvent( pEvent );
}

void LightScene::Update(float deltaTime)
{
    Scene::Update( deltaTime );

    fw::FWCore* pFramework = static_cast<Game*>(m_pGame)->GetFramework();
    m_pCamera->Hack_ThirdPersonCamUpdate( pFramework, deltaTime );

    fw::Component* pComponent = m_pComponentManager->GetComponentOftype(fw::PlayerMovementComponent::GetStaticType());
    fw::PlayerMovementComponent* pPlayerComp = static_cast<fw::PlayerMovementComponent*>(pComponent);
    pPlayerComp->Update(deltaTime);

    
    ImGui::Begin("Camera Debug");
    vec3 pos = m_pCamera->GetTransform()->GetPosition();
    ImGui::Text("Camera Pos: %0.2f, %0.2f, %0.2f", pos.x, pos.y, pos.z);
    ImGui::End();//Camera debug - being undockable was killing me 
}
