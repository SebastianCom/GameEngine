#include "Framework.h"

#include "Assignment2Scene.h"
#include "DataTypes.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/Player.h"
#include "Game.h"

Assignment2Scene::Assignment2Scene(Game* pGame)
    : fw::Scene( pGame )
{
    m_pPhysicsWorld = new fw::PhysicsWorldBox2D( pGame->GetFramework()->GetEventManager() );
    m_pPhysicsWorld->SetGravity( vec3( 0, -10, 0 ) );

    m_pCamera = new fw::Camera( this, vec3(2, 0, -15) );
    m_pCamera->SetLookAtPosition( vec3(2, 0, 0) );

    m_pPlayerController = new PlayerController( pGame->GetFramework()->GetEventManager() );

    //New Player
    fw::GameObject* pPlayer = new fw::GameObject("Player", this, vec3(3, 5, 0));
    pPlayer->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("Purple")));
    pPlayer->AddComponent(new fw::PlayerMovementComponent(m_pPlayerController, pPlayer));
    pPlayer->CreateBody(m_pPhysicsWorld, true, 1);
    pPlayer->GetPhysicsBody()->RegisterForEvents(pGame->GetFramework()->GetEventManager());
    m_Objects.push_back(pPlayer);
    //New Spinner
    fw::GameObject* pSpinner = new fw::GameObject("Spinner", this, vec3(0, 5, 0));
    pSpinner->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("Pink")));
    pSpinner->AddComponent(new fw::PlayerMovementComponent(m_pPlayerController, pPlayer));
    pSpinner->CreateBody(m_pPhysicsWorld, true, 1);
    pSpinner->CreateJointDef(m_pPhysicsWorld, vec3(0, 5, 0), fw::JointType::Revolute, nullptr);
    pSpinner->m_pRevJoint->EnableMotor(true);
    pSpinner->m_pRevJoint->SetMotorSpeed(20.0f);
    pSpinner->m_pRevJoint->SetMaxMotorTorque(3.0f);

    m_Objects.push_back(pSpinner);

    // Ground Object.
    fw::GameObject* pGameObject = new fw::GameObject( "Ground", this, vec3(3,-6,0) );
    pGameObject->AddComponent( new fw::MeshComponent( pGame->GetMesh("Sprite"), pGame->GetMaterial("LightBlue") ) );
    pGameObject->GetTransform()->SetScale( vec3( 20, 1, 1 ) );
    pGameObject->CreateBody( m_pPhysicsWorld, false, 1 );
    m_Objects.push_back( pGameObject );

}

Assignment2Scene::~Assignment2Scene()
{
    delete m_pPlayerController;
}

void Assignment2Scene::StartFrame(float deltaTime)
{
    m_pPlayerController->StartFrame();
}

void Assignment2Scene::OnEvent(fw::Event* pEvent)
{
    fw::Scene::OnEvent( pEvent );
}

void Assignment2Scene::Update(float deltaTime)
{
    Scene::Update( deltaTime );

    float time = (float)fw::GetSystemTimeSinceGameStart() * 20;

    HandleCollision();


    //TODO
    //MOVE into playermovementcomponent 
    fw::Component* pComponent = m_pComponentManager->GetComponentOftype(fw::PlayerMovementComponent::GetStaticType());
    fw::PlayerMovementComponent* pPlayerComp = static_cast<fw::PlayerMovementComponent*>(pComponent);
    pPlayerComp->Update(deltaTime);


    

}

void Assignment2Scene::HandleCollision()
{
    if (CollObjectA) //&& CollObjectB)
    {
        if (CollObjectA->GetName() == "Player")
        {
            assert(true);
        }
    }
}
