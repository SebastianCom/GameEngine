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

    //Player
    fw::GameObject* pPlayer = new fw::GameObject("Player", this, vec3(3, 5, 0));
    pPlayer->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("Purple")));
    pPlayer->AddComponent(new fw::PlayerMovementComponent(m_pPlayerController, pPlayer));
    pPlayer->CreateBody(m_pPhysicsWorld, true, 1);
    m_Objects.push_back(pPlayer);
    
    //Spinner - Revolute and friction joints with a motor
    fw::GameObject* pSpinner = new fw::GameObject("Spinner", this, vec3(0, 5, 0));
    pSpinner->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("Pink")));
    pSpinner->CreateBody(m_pPhysicsWorld, true, 1);
    pSpinner->GetPhysicsBody()->RegisterForEvents(pGame->GetFramework()->GetEventManager());
    pSpinner->CreateJoint(m_pPhysicsWorld, vec3(0, 5, 0), fw::JointType::Revolute, nullptr); //This joint also has a friction joint
    pSpinner->m_pRevJoint->SetMotorSpeed(20.0f);
    pSpinner->m_pRevJoint->SetMaxMotorTorque(3.0f);
    m_pSpinner = pSpinner->m_pRevJoint;
    m_Objects.push_back(pSpinner);

    //Gear Spinner - revolute and gear joint that works with the spinner
    fw::GameObject* pGearSpinner = new fw::GameObject("GearSpinner", this, vec3(5, 5, 0));
    pGearSpinner->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("Red")));
    pGearSpinner->CreateBody(m_pPhysicsWorld, true, 1);
    pGearSpinner->CreateJoint(m_pPhysicsWorld, vec3(5, 5, 0), fw::JointType::Revolute, nullptr); //Keep it in spot
    pGearSpinner->CreateJoint(m_pPhysicsWorld, pSpinner->m_pRevJoint, pGearSpinner->m_pRevJoint, pSpinner->GetPhysicsBody()->GetBody()); 
    m_Objects.push_back(pGearSpinner);

    //Distance - distance joint that works with the player
    fw::GameObject* pDistance = new fw::GameObject("Distance Joint", this, vec3(6, 5, 0));
    pDistance->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("White")));
    pDistance->CreateBody(m_pPhysicsWorld, true, 1);
    pDistance->CreateJoint(m_pPhysicsWorld, vec3(5, 5, 0), fw::JointType::Distance, pPlayer->GetPhysicsBody()->GetBody());
    m_Objects.push_back(pDistance);

    //Right Blocker non dynamic obstacle used to show the distance joint
    fw::GameObject* pBlocker = new fw::GameObject("Right Blocker", this, vec3(9.6f, -5.0f, 0));
    pBlocker->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("Green")));
    pBlocker->CreateBody(m_pPhysicsWorld, false, 1);
    m_Objects.push_back(pBlocker);

    //Left Blocker non dynamic obstacle used to show the distance joint
    fw::GameObject* pLBlocker = new fw::GameObject("Left Blocker", this, vec3(-6.7f, -5.0f, 0));
    pLBlocker->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("Green")));
    pLBlocker->CreateBody(m_pPhysicsWorld, false, 1);
    m_Objects.push_back(pLBlocker);


    //Spinner Sensor - toggles the motor of the spinner on and off
    fw::GameObject* pSpinnerToggle = new fw::GameObject("SpinnerSensor", this, vec3(-5.6f, -5.0f, 0));
    pSpinnerToggle->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("SpinnerToggle")));
    pSpinnerToggle->CreateBody(m_pPhysicsWorld, false, 1, true); //Creates Sensor 
    m_Objects.push_back(pSpinnerToggle);



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

    ImGui::Begin("Spinner Debug"); //Spinner start
    ImGui::Text("Collision only happpens when below false");
    ImGui::Text("Timer: %f", m_CollisionTimer);
    const char* temp;
    if (m_bCollision == true)
         temp = "true";
    else
        temp = "false";
    ImGui::Text(temp);
    ImGui::End(); //Spinner end

    fw::Component* pComponent = m_pComponentManager->GetComponentOftype(fw::PlayerMovementComponent::GetStaticType());
    fw::PlayerMovementComponent* pPlayerComp = static_cast<fw::PlayerMovementComponent*>(pComponent);
    pPlayerComp->Update(deltaTime);

    //Timer between collisions
    if (m_bCollision == true && m_CollisionTimer > 0.0f)
    {
        m_CollisionTimer -= deltaTime;
    }
    else if (m_CollisionTimer <= 0.0f && m_bCollision == true)
    {
        m_bCollision = false;
    }
    

}

void Assignment2Scene::HandleCollision()
{
    if (CollObjectA && CollObjectB)
    {
        //Spinner 
        if (CollObjectA->GetName() == "Player")
        {
            if (CollObjectB->GetName() == "SpinnerSensor")
            {
                if (m_CollisionTimer <= 0.0f)
                {
                    SpinnerToggle = !SpinnerToggle;
                    m_pSpinner->EnableMotor(SpinnerToggle);

                    m_bCollision = true;
                    m_CollisionTimer = 1.0f;
                }

            }
        }

        //Next Motor
    }
}
