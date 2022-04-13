#include "Framework.h"

#include "CubeScene.h"
#include "DataTypes.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/Player.h"
#include "Game.h"

CubeScene::CubeScene(Game* pGame)
    : fw::Scene( pGame )
{
    m_pCamera = new fw::Camera(this, vec3(0, 0, -15));
    m_pCamera->SetLookAtPosition(vec3(0, 0, 0));
    
    // Cube Object.
    fw::GameObject* pGameObject = new fw::GameObject( "Cube", this, vec3(0,0,0) );
    pGameObject->AddComponent(new fw::MeshComponent(pGame->GetMesh("Cube"), pGame->GetMaterial("Purple")));
    pGameObject->GetTransform()->SetScale(2);
    m_Objects.push_back( pGameObject );
}

CubeScene::~CubeScene()
{
}

void CubeScene::StartFrame(float deltaTime)
{
}

void CubeScene::OnEvent(fw::Event* pEvent)
{
    fw::Scene::OnEvent( pEvent );
}

void CubeScene::Update(float deltaTime)
{
    Scene::Update( deltaTime );

    float time = (float)fw::GetSystemTimeSinceGameStart() * 20;
    m_Objects[0]->GetTransform()->SetRotation( vec3( time*4, time*4, 0 ) );

}
