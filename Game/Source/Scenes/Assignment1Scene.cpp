#include "Framework.h"

#include "Assignment1Scene.h"
#include "DataTypes.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/Player.h"
#include "GameObjects/Meteor.h"
#include "Game.h"
#include "Components/MeshComponent.h"
#include "Objects/Material.h"
#include "Math/Random.h"



Assignment1Scene::Assignment1Scene(Game* pGame)
    :fw::Scene( pGame )
{

    m_pPhysicsWorld = new fw::PhysicsWorldBox2D(pGame->GetFrameWork()->GetEventManager());
    m_pPhysicsWorld->SetGravity(vec2(0, -10));
    m_pCamera = new fw::Camera(this, vec3(0, 0, -20), vec3(0,0,0), 45.0f); 
    m_pPlayerController = new PlayerController();

    fw::GameObject* BackGround = new fw::GameObject("Background", this, vec3(-9, -9, 1));
    BackGround->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("BackGround")));
    BackGround->SetScale(vec2(18, 18));
    m_ActiveObjects.push_back(BackGround);

    Player* pPlayer = new Player(this,vec2(0, 0), m_pPlayerController);
    
    //Change to ewe
    pPlayer->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("Ewe")));
    pPlayer->CreateBody(m_pPhysicsWorld, true, vec2(1, 1), 1);
    
    m_ActiveObjects.push_back(pPlayer);
    
    //Change to ground
    fw::GameObject* pGround = new fw::GameObject("Ground", this, vec2(0, -6));
    pGround->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("Ground")));
    pGround->CreateBody(m_pPhysicsWorld, true, vec2(8, 1), 0);
    m_ActiveObjects.push_back(pGround);


    //BoundsBox
    fw::GameObject* pBoundsBox = new fw::GameObject("BoundsBox", this, vec2(0, -7));
    pBoundsBox->CreateBody(m_pPhysicsWorld, false, vec2(20, 1), 0);
    pBoundsBox->m_pPhysicsBody->GetBody()->SetType(b2BodyType::b2_staticBody);
    m_ActiveObjects.push_back(pBoundsBox);


    for (int i = 0; i < NumMeteor; i++) //Sprite is not linked to body? - yeah because the object is not updated unless added to m_activeObjects.
    {
        m_pMeteors.push_back(new Meteor(this, vec2(0, 0)));
       // m_pMeteors[i]->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("Meteor")));
        m_pMeteors[i]->CreateBody(m_pPhysicsWorld, true, vec2(.5f, .5f), 1, "Circle"); //MAKE CIRCLE
        m_pMeteors[i]->m_pPhysicsBody->GetBody()->SetEnabled(false);
    }
    



    bCollision = false;

    m_pMesh = pGame->GetMesh("Sprite");
    m_pMat = pGame->GetMaterial("Meteor");

   m_Material = pGame->GetMaterial("Ground");
}

Assignment1Scene::~Assignment1Scene()
{
    delete m_pPlayerController;
}

void Assignment1Scene::StartFrame(float deltaTime)
{
    m_pPlayerController->StartFrame();
}

void Assignment1Scene::OnEvent(fw::Event* pEvent)
{
    m_pPlayerController->OnEvent(pEvent);
    fw::Scene::OnEvent(pEvent);

    CheckForCollision();

}

void Assignment1Scene::CheckForCollision()
{
    Player* pPlayer = dynamic_cast<Player*>(CollObjectA);
    fw::GameObject* pGround = dynamic_cast<fw::GameObject*>(CollObjectA);
 
    //Meteor Wil never be CollA, CollA is called first and Player and Enviroment come before the Metors. After player is destoryed meteors will only
    //collide with enviroment which will always be ahead of the Metoers in the order. 


    if (pPlayer) //CollA is player
    {
        Meteor* pMeteor = dynamic_cast<Meteor*>(CollObjectB);
        fw::GameObject* pGround = dynamic_cast<fw::GameObject*>(CollObjectB);

        if (pMeteor)
        {
            for (int i = 0; i < m_ActiveObjects.size(); i++)
            {
                Meteor* MeteorToRemove = dynamic_cast<Meteor*>(m_ActiveObjects[i]);
                if (MeteorToRemove == pMeteor)
                {
                    //Player go boom
                    //Spawn meat chunks
                    m_ActiveObjects.erase(std::next(m_ActiveObjects.begin(), i));
                    m_pMeteors.push_back(MeteorToRemove);
                    m_pMeteors.back()->m_pPhysicsBody->GetBody()->SetEnabled(false);
                    m_pMeteors.back()->SetPosition(vec2(0, 11));
                    m_pMeteors.back()->m_pPhysicsBody->SetPosition(m_pMeteors.back()->GetPosition());
                    // m_pMeteors.back()->RemoveComponent();
                    break; 
                }
            }
        }
        if (pGround && pGround->m_pPhysicsBody->GetBody()->GetType() != b2BodyType::b2_staticBody)
        {
            if (pGround)
            {
                pPlayer->bOnGround = true;
                bCollision = true;
            }
            else
            {
                bCollision = false;
            }
        }
        else if (pGround && pGround->m_pPhysicsBody->GetBody()->GetType() == b2BodyType::b2_staticBody)
        {
            for (int i = 0; i < m_ActiveObjects.size(); i++)
            {
                Player* PlayerToRemove = dynamic_cast<Player*>(m_ActiveObjects[i]);
                if (PlayerToRemove)
                {
                    //REMOVE PLAYER COMPONET
                    m_ActiveObjects.erase(std::next(m_ActiveObjects.begin(), i));
                    break;
                }
            }
        }
    }
    else if (pGround) //CollA is Meteor
    {
        Meteor* pMeteor = dynamic_cast<Meteor*>(CollObjectB);

        if (pMeteor)
        {
            for (int i = 0; i < m_ActiveObjects.size(); i++)
            {
                Meteor* MeteorToRemove = dynamic_cast<Meteor*>(m_ActiveObjects[i]);
                if (MeteorToRemove == pMeteor)
                {
                    if (pGround->m_pPhysicsBody->GetBody()->GetType() != b2BodyType::b2_staticBody)
                        ShakeCam = true;
                    m_ActiveObjects.erase(std::next(m_ActiveObjects.begin(), i));
                    m_pMeteors.push_back(MeteorToRemove);
                    m_pMeteors.back()->m_pPhysicsBody->GetBody()->SetEnabled(false);
                    m_pMeteors.back()->SetPosition(vec2(0, 11));
                    m_pMeteors.back()->m_pPhysicsBody->SetPosition(m_pMeteors.back()->GetPosition());
                    break;
                }
            }
        }
    }
}

void Assignment1Scene::Reset()
{
    //m_ActiveObjects[0]->SetPosition(vec2(0, 5));

}

void Assignment1Scene::SpawnRandomMeteor()
{
    fw::GameObject* ObjectToSpawn = m_pMeteors.back();
    m_pMeteors.pop_back();
    m_ActiveObjects.push_back(ObjectToSpawn);
    float RandomX = fw::Random::GetFloat(-5.0f, 5.0f);
    m_ActiveObjects.back()->SetPosition(vec2(0, 11));
    m_ActiveObjects.back()->m_pPhysicsBody->SetPosition(m_ActiveObjects.back()->GetPosition());
    m_ActiveObjects.back()->AddComponent(new fw::MeshComponent(m_pMesh, m_pMat));
    m_ActiveObjects.back()->m_pPhysicsBody->GetBody()->SetEnabled(true);
    m_ActiveObjects.back()->m_pPhysicsBody->GetBody()->ApplyForceToCenter(b2Vec2(fw::Random::GetInt(-500, 500),-3000), true); //target poistion - transform postion * multiplication faction


}

void Assignment1Scene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
    b2Vec2 Position = vec2(m_ActiveObjects[1]->GetPosition().x, m_ActiveObjects[1]->GetPosition().y);
    b2Vec2 Position2 = vec2(m_ActiveObjects[1]->m_pPhysicsBody->GetBody()->GetPosition().x, m_ActiveObjects[1]->m_pPhysicsBody->GetBody()->GetPosition().y);
    ImGui::Text("%0.2f, %0.2f, %0.2f", Position.x, Position.y, 0);
    ImGui::Text("%0.2f, %0.2f, %0.2f", Position2.x, Position2.y, 0);
    ImGui::Checkbox("Collision", &bCollision);

    if (ImGui::Button("ShakeCam"))
    {
       ShakeCam = true;
    }

    if (ShakeCam)
       ShakeCam =  m_pCamera->CameraShake(deltaTime);

    //m_pCamera->SetPosition(vec3(100,100,-20));
    m_pPhysicsWorld->Draw(m_pCamera, m_Material);
    
    if (SpawnTimer > 0)
    {
        SpawnTimer -= deltaTime;
    }
    else if (SpawnTimer <= 0)
    {
        SpawnRandomMeteor();
        SpawnTimer = 2.0f;
    }




}