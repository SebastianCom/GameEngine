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
#include "GameObjects/MeatChunk.h"



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

    fw::GameObject* TitleScreen = new fw::GameObject("Title", this, vec3(-3, 0, 0));
    m_pTitleMeshComp = new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("Start"));
    TitleScreen->AddComponent(m_pTitleMeshComp);
    TitleScreen->SetScale(vec2(7, 1));
    m_ActiveObjects.push_back(TitleScreen);

    //fw::GameObject* EndScreen = new fw::GameObject("End", this, vec3(-9, -9, 1));
    //m_pEndMeshComp = new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("End"));
    //EndScreen->SetScale(vec2(1, 1));
    //m_ActiveObjects.push_back(EndScreen);

    Player* pPlayer = new Player(this,vec2(0, -5), m_pPlayerController);
    
    //Change to ewe
    m_pEweMeshComp = new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("Ewe"));
    pPlayer->AddComponent(m_pEweMeshComp);
    pPlayer->CreateBody(m_pPhysicsWorld, true, vec2(1, 1), 1);
    pPlayer->m_pPhysicsBody->GetBody()->SetEnabled(true);
    
    m_ActiveObjects.push_back(pPlayer);

    //CHUNKSSSSS
    for (int i = 0; i < NumChunks; i++) //Sprite is not linked to body? - yeah because the object is not updated unless added to m_activeObjects.
    {
        m_pMeatChunks.push_back(new MeatChunk(this, vec2(0, 0)));
        m_pMeatChunks[i]->CreateBody(m_pPhysicsWorld, true, vec2(.35f, .35f), 1, "Circle"); //MAKE CIRCLE
        m_pMeatChunks[i]->m_pPhysicsBody->GetBody()->SetEnabled(false);
    }


    
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

    m_pMeteorMesh = pGame->GetMesh("Sprite");
    m_pMeteorMat = pGame->GetMaterial("Meteor");
    m_Material = pGame->GetMaterial("Ground");
   
    m_pChunkMesh = pGame->GetMesh("Sprite");
    m_pMeatMat = pGame->GetMaterial("Meat");
    m_pBoneMat = pGame->GetMaterial("Bone");

    m_pEndMeshComp = new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("End"));
    m_pWinMeshComp = new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("Win"));

    ////Test
    //fw::GameObject* ChunkToSpawn = m_pMeatChunks.back();
    //m_pMeatChunks.pop_back();
    //m_ActiveObjects.push_back(ChunkToSpawn);
    //m_ActiveObjects.back()->SetPosition(vec3(1,-3,0));
    //m_ActiveObjects.back()->m_pPhysicsBody->SetPosition(m_ActiveObjects.back()->GetPosition());
    //m_pChunksMeshComp = new fw::MeshComponent(m_pChunkMesh, m_pBoneMat);
    //m_ActiveObjects.back()->AddComponent(m_pChunksMeshComp);
    //m_ActiveObjects.back()->m_pPhysicsBody->GetBody()->SetEnabled(true);
   
}

Assignment1Scene::~Assignment1Scene()
{
        delete m_pPlayerController;

     //delete  m_pMeteorMeshComp;
     //delete    m_pEweMeshComp;
     //delete   m_pChunksMeshComp;
     //delete m_pTitleMeshComp;
     //delete   m_pEndMeshComp;
}

void Assignment1Scene::StartFrame(float deltaTime)
{
    m_pPlayerController->StartFrame();
}

void Assignment1Scene::OnEvent(fw::Event* pEvent)
{
    if(GameStarted)
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
                    m_pMeteors.back()->RemoveComponent(m_pMeteorMeshComp);
                    for (int j = 0; j < m_ActiveObjects.size(); j++)
                    {
                        Player* pPlayerToRemove = dynamic_cast<Player*>(m_ActiveObjects[j]);
                        if (pPlayerToRemove)
                        {
                            m_ActiveObjects[j]->RemoveComponent(m_pEweMeshComp);
                            PlayerCompRemoved = true;
                            m_ActiveObjects[j]->m_pPhysicsBody->GetBody()->SetEnabled(false);
                            SpawnMeatChuncks(pPlayerToRemove->GetPosition());
                            for (int i = 0; i < m_ActiveObjects.size(); i++)
                            {

                                if (m_ActiveObjects[i]->GetName() == "Title")
                                {
                                    m_ActiveObjects[i]->AddComponent(m_pEndMeshComp);
                                    m_pCurrentTitleMesh = m_pEndMeshComp;
                                }
                            }
                            break;
                        }
                    }
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
                    m_ActiveObjects[i]->RemoveComponent(m_pEweMeshComp);
                    PlayerCompRemoved = true;
                    m_ActiveObjects[i]->m_pPhysicsBody->GetBody()->SetEnabled(false);
                    for (int i = 0; i < m_ActiveObjects.size(); i++)
                    {

                        if (m_ActiveObjects[i]->GetName() == "Title")
                        {
                            m_ActiveObjects[i]->AddComponent(m_pWinMeshComp);
                            m_pCurrentTitleMesh = m_pWinMeshComp;
                        }
                    }
                    //m_ActiveObjects.erase(std::next(m_ActiveObjects.begin(), i));
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
                    m_pMeteors.back()->RemoveComponent(m_pMeteorMeshComp);
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
    m_pMeteorMeshComp = new fw::MeshComponent(m_pMeteorMesh, m_pMeteorMat);
    m_ActiveObjects.back()->AddComponent(m_pMeteorMeshComp);
    m_ActiveObjects.back()->m_pPhysicsBody->GetBody()->SetEnabled(true);
    m_ActiveObjects.back()->m_pPhysicsBody->GetBody()->ApplyForceToCenter(b2Vec2(fw::Random::GetInt(-250, 250),-3000), true); //target poistion - transform postion * multiplication faction


}

void Assignment1Scene::SpawnMeatChuncks(fw::vec3 Pos)
{

    for (int i = NumChunks; i > 0; i--)
    {
        fw::GameObject* ChunkToSpawn = m_pMeatChunks.back();
        m_pMeatChunks.pop_back();
        m_ActiveObjects.push_back(ChunkToSpawn);
        m_ActiveObjects.back()->SetPosition(Pos);
        m_ActiveObjects.back()->m_pPhysicsBody->SetPosition(m_ActiveObjects.back()->GetPosition());
        
        int WhichType = fw::Random::GetInt(0, 1);

        if (WhichType == 0)
        {
            m_pChunksMeshComp = new fw::MeshComponent(m_pChunkMesh, m_pBoneMat);
        }
        else
        {
            m_pChunksMeshComp = new fw::MeshComponent(m_pChunkMesh, m_pMeatMat);
        }    
        m_ActiveObjects.back()->AddComponent(m_pChunksMeshComp);
        m_ActiveObjects.back()->m_pPhysicsBody->GetBody()->SetEnabled(true);
        m_ActiveObjects.back()->m_pPhysicsBody->GetBody()->ApplyForceToCenter(b2Vec2(fw::Random::GetInt(-250, 250), fw::Random::GetInt(100, 500)), true);
        m_ActiveObjects.back()->m_pPhysicsBody->GetBody()->ApplyTorque(fw::Random::GetFloat(-10.0f, 10.0f), true);
    }
}

void Assignment1Scene::ResetButton()
{
    
   for (int i = m_ActiveObjects.size() - 1; i > -1; i--)
   {
       Player* pPlayer = dynamic_cast<Player*>(m_ActiveObjects[i]);
       Meteor* pMeteor = dynamic_cast<Meteor*>(m_ActiveObjects[i]);
       MeatChunk* pChunk = dynamic_cast<MeatChunk*>(m_ActiveObjects[i]);

       //Reset Meteors
       if (pMeteor)
       {
           m_ActiveObjects.erase(std::next(m_ActiveObjects.begin(), i));
           m_pMeteors.push_back(pMeteor);
           m_pMeteors.back()->m_pPhysicsBody->GetBody()->SetEnabled(false);
           m_pMeteors.back()->SetPosition(vec2(0, 11));
           m_pMeteors.back()->m_pPhysicsBody->SetPosition(m_pMeteors.back()->GetPosition());
           m_pMeteors.back()->RemoveComponent(m_pMeteorMeshComp);
       }
       //Reset CHUNKSSSSS
       else if (pChunk)
       {
           m_ActiveObjects.erase(std::next(m_ActiveObjects.begin(), i));
           m_pMeatChunks.push_back(pChunk);
           m_pMeatChunks.back()->m_pPhysicsBody->GetBody()->SetEnabled(false);
           m_pMeatChunks.back()->SetPosition(vec2(10, 11));
           m_pMeatChunks.back()->m_pPhysicsBody->SetPosition(m_pMeatChunks.back()->GetPosition());
           if(!MeatCompRemoved)
           m_pMeatChunks.back()->RemoveComponent(m_pChunksMeshComp);
           MeatCompRemoved = true;
       }
       //Reset Timers and Bools
       //Reset Player
       else if (pPlayer)
       {
           for (int i = 0; i < m_ActiveObjects.size(); i++)
           {

               if (m_ActiveObjects[i]->GetName() == "Title")
               {
                   if (m_pCurrentTitleMesh == m_pEndMeshComp)
                   {
                    m_ActiveObjects[i]->RemoveComponent(m_pEndMeshComp);
                    m_pCurrentTitleMesh = nullptr;
                    break;
                   }
                   else if (m_pCurrentTitleMesh == m_pWinMeshComp)
                   {
                     m_ActiveObjects[i]->RemoveComponent(m_pWinMeshComp);
                     m_pCurrentTitleMesh = nullptr;
                     break;
                   }
               }
           }

           if(PlayerCompRemoved == true)
           {
               m_ActiveObjects[i]->AddComponent(m_pEweMeshComp);   
               PlayerCompRemoved = false;
           }
           m_ActiveObjects[i]->SetPosition(vec3(0,-5,0));
           m_ActiveObjects[i]->SetRotation(vec3(0,0,0));
           m_ActiveObjects[i]->m_pPhysicsBody->GetBody()->SetTransform(b2Vec2(0,-5), 0);
           m_ActiveObjects[i]->m_pPhysicsBody->GetBody()->SetEnabled(true);
           m_ActiveObjects[i]->m_pPhysicsBody->GetBody()->SetLinearVelocity(b2Vec2(0,0));
           m_ActiveObjects[i]->m_pPhysicsBody->GetBody()->SetAngularVelocity(0);
       }

       //bCollision = !bCollision;

       SpawnTimer = 2.0f;


      
   }

   for (int i = 0; i < m_ActiveObjects.size(); i++)
   {

       if (m_ActiveObjects[i]->GetName() == "Title")
       {
           m_ActiveObjects[i]->AddComponent(m_pTitleMeshComp);
       }
   }

   MeatCompRemoved = false;
   GameStarted = false;
  
}

void Assignment1Scene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
    b2Vec2 Position = vec2(m_ActiveObjects[1]->GetPosition().x, m_ActiveObjects[1]->GetPosition().y);
    //b2Vec2 Position2 = vec2(m_ActiveObjects[1]->m_pPhysicsBody->GetBody()->GetPosition().x, m_ActiveObjects[1]->m_pPhysicsBody->GetBody()->GetPosition().y);
    ImGui::Text("%0.2f, %0.2f, %0.2f", Position.x, Position.y, 0);
    //ImGui::Text("%0.2f, %0.2f, %0.2f", Position2.x, Position2.y, 0);
    ImGui::Checkbox("Collision", &bCollision);

    if (ImGui::Button("ShakeCam"))
    {
       ShakeCam = true;
    }

    if (ImGui::Button("Game Start"))
    {
        GameStarted = true;
        SpawnTimer = 0.01f;

        for (int i = 0; i < m_ActiveObjects.size(); i++)
        {
           
            if (m_ActiveObjects[i]->GetName() == "Title")
            {
                m_ActiveObjects[i]->RemoveComponent(m_pTitleMeshComp);
            }
        }
        
    }

    if (ImGui::Button("Game Stop"))
    {
        if(GameStarted)
        ResetButton();
    }

       
    if (ShakeCam)
       ShakeCam =  m_pCamera->CameraShake(deltaTime);

    //m_pCamera->SetPosition(vec3(100,100,-20));
    m_pPhysicsWorld->Draw(m_pCamera, m_Material);
    
    if (GameStarted)
    {
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




}