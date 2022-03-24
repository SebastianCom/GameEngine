#include "Framework.h"

#include "WaterScene.h"
#include "DataTypes.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/Player.h"
#include "Game.h"

WaterScene::WaterScene(Game* pGame)
    : fw::Scene( pGame )
{
    m_pCamera = new fw::Camera( this, vec3(0, 4, -10) );
    m_pCamera->SetLookAtPosition( vec3(0,0,0) );

    fw::GameObject* pWaterPlane = new fw::GameObject( "Water", this, vec3(-5.0f, 0, -5.0f) );
    pWaterPlane->AddComponent( new fw::MeshComponent( pGame->GetMesh("Plane"),
                                                      pGame->GetMaterial("Water") ) );
    m_Objects.push_back( pWaterPlane );

    //m_pCamera->SetObjectWeAreLookingAt( pWaterPlane );
}

WaterScene::~WaterScene()
{
}

void WaterScene::StartFrame(float deltaTime)
{
}

void WaterScene::OnEvent(fw::Event* pEvent)
{
    fw::Scene::OnEvent( pEvent );
}

void WaterScene::Update(float deltaTime)
{
    Scene::Update( deltaTime );
}
