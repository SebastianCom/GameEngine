#include "Framework.h"

#include "WaterScene.h"
#include "DataTypes.h"
#include "Game.h"
#include "Components/MeshComponent.h"


 WaterScene::WaterScene(Game* pGame)
  :fw::Scene( pGame )
{
    m_pPhysicsWorld = new fw::PhysicsWorldBox2D();
    m_pCamera = new fw::Camera(this, vec3(115, 25, 500), vec3(115,-300,-100), 25.0f); //REMEBER TO REBUILD IF YOU CHANGE FOV
    fw::GameObject* pWaterObject = new fw::GameObject(this, vec2(-4, -4));
    pWaterObject->AddComponent(new fw::MeshComponent(pGame->GetMesh("Plane"), pGame->GetMaterial("Water")));
    pWaterObject->CreateBody(m_pPhysicsWorld, true, vec2(1, 1), 0);
    m_Objects.push_back(pWaterObject);

}

 WaterScene::WaterScene(Game* pGame, vec3 CamPos, fw::vec3 CamLook)
     :fw::Scene(pGame)
 {
     m_pPhysicsWorld = new fw::PhysicsWorldBox2D();
     m_pCamera = new fw::Camera(this, CamPos, CamLook, 45.0f); //REMEBER TO REBUILD IF YOU CHANGE FOV
     fw::GameObject* pWaterObject = new fw::GameObject(this, vec2(-4, -4));
     pWaterObject->AddComponent(new fw::MeshComponent(pGame->GetMesh("Plane"), pGame->GetMaterial("Water")));
     pWaterObject->CreateBody(m_pPhysicsWorld, true, vec2(1, 1), 0);
     m_Objects.push_back(pWaterObject);

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