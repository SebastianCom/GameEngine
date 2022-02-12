#include "Framework.h"

#include "WaterScene.h"
#include "DataTypes.h"
#include "Game.h"
#include "Components/MeshComponent.h"



    WaterScene::WaterScene(Game* pGame)
    :fw::Scene( pGame )
{
    m_pPhysicsWorld = new fw::PhysicsWorldBox2D();
    m_pCamera = new fw::Camera(this, vec3(15, 15, -25), vec3(15,0,15), 15.0f); //REMEBER TO REBUILD IF YOU CHANGE FOV
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