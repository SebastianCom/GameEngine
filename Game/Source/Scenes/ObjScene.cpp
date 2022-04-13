#include "Framework.h"

#include "ObjScene.h"
#include "DataTypes.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/Player.h"
#include "Game.h"

ObjScene::ObjScene(Game* pGame)
    : fw::Scene( pGame )
{
    m_pCamera = new fw::Camera(this, vec3(0, 0, -15));
    m_pCamera->SetLookAtPosition(vec3(0, 0, 0));
    
    // Cube Object.
    fw::GameObject* pGameObject = new fw::GameObject( "Cube", this, vec3(0,0,0) );
    pGameObject->AddComponent(new fw::MeshComponent(pGame->GetMesh("Obj"), pGame->GetMaterial("Purple")));
    m_Objects.push_back( pGameObject );

    fw::GameObject* pGameObject2 = new fw::GameObject("Glock", this, vec3(5, 0, 0));
    pGameObject2->AddComponent(new fw::MeshComponent(pGame->GetMesh("ObjGun"), pGame->GetMaterial("Pink")));
    pGameObject2->GetTransform()->SetScale(vec3(.1f, .1f, .1f));
    m_Objects.push_back(pGameObject2);

    fw::GameObject* pGameObject3 = new fw::GameObject("Glock", this, vec3(-5, 0, 0));
    pGameObject3->AddComponent(new fw::MeshComponent(pGame->GetMesh("ObjTree"), pGame->GetMaterial("Red")));
    pGameObject3->GetTransform()->SetScale(vec3(.1f, .1f, .1f));
    m_Objects.push_back(pGameObject3);
}

ObjScene::~ObjScene()
{
}

void ObjScene::StartFrame(float deltaTime)
{
}

void ObjScene::OnEvent(fw::Event* pEvent)
{
    fw::Scene::OnEvent( pEvent );
}

void ObjScene::Update(float deltaTime)
{
    Scene::Update( deltaTime );

    float time = (float)fw::GetSystemTimeSinceGameStart() * 20;
    m_Objects[0]->GetTransform()->SetRotation( vec3( time*4, time, 0 ) );
    m_Objects[1]->GetTransform()->SetRotation( vec3( time*4, time, 0 ) );
    m_Objects[2]->GetTransform()->SetRotation( vec3( time*4, time, 0 ) );
}
