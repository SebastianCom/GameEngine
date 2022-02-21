#include "Framework.h"

#include "WaterScene.h"
#include "DataTypes.h"
#include "Game.h"
#include "Components/MeshComponent.h"


 WaterScene::WaterScene(Game* pGame)
  :fw::Scene( pGame )
{
    m_pPhysicsWorld = new fw::PhysicsWorldBox2D(pGame->GetFrameWork()->GetEventManager());
    //m_pCamera = new fw::Camera(this, vec3(115, 25, 500), vec3(115,-300,-100), 25.0f); //REMEBER TO REBUILD IF YOU CHANGE FOV
    m_pCamera = new fw::Camera(this, vec3(-5, 15, -5), vec3(25,0,25), 45.0f); //REMEBER TO REBUILD IF YOU CHANGE FOV
    fw::GameObject* pWaterObject = new fw::GameObject(this, vec2(-4, -4));
    pWaterObject->AddComponent(new fw::MeshComponent(pGame->GetMesh("Plane"), pGame->GetMaterial("Water")));
    pWaterObject->CreateBody(m_pPhysicsWorld, true, vec2(1, 1), 0);
    m_ActiveObjects.push_back(pWaterObject);

}

 WaterScene::WaterScene(Game* pGame, vec3 CamPos, fw::vec3 CamLook) // This is to make the scene with a custom camera
     :fw::Scene(pGame)
 {
     m_pPhysicsWorld = new fw::PhysicsWorldBox2D(pGame->GetFrameWork()->GetEventManager());
     m_pCamera = new fw::Camera(this, CamPos, CamLook, 45.0f); //REMEBER TO REBUILD IF YOU CHANGE FOV
     fw::GameObject* pWaterObject = new fw::GameObject(this, vec2(-4, -4));
     pWaterObject->AddComponent(new fw::MeshComponent(pGame->GetMesh("Plane"), pGame->GetMaterial("Water")));
     pWaterObject->CreateBody(m_pPhysicsWorld, true, vec2(1, 1), 0);
     m_ActiveObjects.push_back(pWaterObject);

 }

WaterScene::~WaterScene()
{

}

void WaterScene::StartFrame(float deltaTime)
{

}

void WaterScene::OnEvent(fw::Event* pEvent)
{
    fw::Scene::OnEvent(pEvent);
}

void WaterScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
    

}