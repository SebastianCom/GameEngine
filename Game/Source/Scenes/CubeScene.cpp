#include "Framework.h"

#include "CubeScene.h"
#include "DataTypes.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/Player.h"
#include "Game.h"
#include "Components/MeshComponent.h"
#include "Math/MyMatrix.h"



    CubeScene::CubeScene(Game* pGame)
    :fw::Scene( pGame )
{
    //m_pPhysicsWorld = new fw::PhysicsWorldBox2D();
    //m_pPhysicsWorld->SetGravity(vec2(0, -10));
    //m_pCamera = new fw::Camera(this, vec2(1.5f * 10, 1.5f * 10) / 2, vec3(1,1,1), 45.0f);
    //fw::GameObject* pCubeObject = new fw::GameObject(this, vec2(-1, -1));
    //pCubeObject->AddComponent(new fw::MeshComponent(pGame->GetMesh("Cube"), pGame->GetMaterial("BaseColor")));
    //pCubeObject->CreateBody(m_pPhysicsWorld, true, vec2(1, 1), 0);
    //m_ActiveObjects.push_back(pCubeObject);


    //Obj test dot
    m_pPhysicsWorld = new fw::PhysicsWorldBox2D(pGame->GetFrameWork()->GetEventManager());
    m_pPhysicsWorld->SetGravity(vec2(0, -10));
    m_pCamera = new fw::Camera(this, vec3(0,0, - 10) / 2, vec3(0, 0, 0), 45.0f);
    fw::GameObject* pCubeObject = new fw::GameObject("Cube", this, vec3(0, 0, 0));
    pCubeObject->AddComponent(new fw::MeshComponent(pGame->GetMesh("ObjTest"), pGame->GetMaterial("BaseColor")));
    pCubeObject->CreateBody(m_pPhysicsWorld, true, vec2(1, 1), 0);
    m_ActiveObjects.push_back(pCubeObject);

}

CubeScene::~CubeScene()
{
}

void CubeScene::StartFrame(float deltaTime)
{
}

void CubeScene::OnEvent(fw::Event* pEvent)
{
    fw::Scene::OnEvent(pEvent);

}

void CubeScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
    float time = (float)fw::GetSystemTimeSinceGameStart() * 50;
    m_ActiveObjects[0]->SetRotation(vec3(time, time, 0));
    //ImGui::Text("%0.2f, %0.2f, %0.2f", m_ActiveObjects[0]->GetRotation().x, m_ActiveObjects[0]->GetRotation().y, m_ActiveObjects[0]->GetRotation().z);
}