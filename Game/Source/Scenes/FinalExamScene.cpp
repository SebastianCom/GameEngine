#include "Framework.h"

#include "FinalExamScene.h"
#include "DataTypes.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/Player.h"
#include "Game.h"

FinalScene::FinalScene(Game* pGame)
    : fw::Scene( pGame )
{

    m_pFramework = pGame->GetFramework();
    m_pCamera = new fw::Camera(this, vec3(0, 0, -15));
    m_pCamera->SetLookAtPosition(vec3(0, 0, 0));
    
    // Player Object.
    fw::GameObject* pPlayer = new fw::GameObject( "pPlayer", this, vec3(3,0,0) );
    pPlayer->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("RPS")));
    pPlayer->GetComponent<fw::MeshComponent>()->SetUVScale(vec2(.01f, 0.01f));
    pPlayer->GetComponent<fw::MeshComponent>()->SetUVOffset(vec2(.3f, 0.f));
    pPlayer->GetTransform()->SetScale(2);
    m_Objects.push_back(pPlayer);

    // Ai Object.
    fw::GameObject* pAi = new fw::GameObject("Cube", this, vec3(-3, 0, 0));
    pAi->AddComponent(new fw::MeshComponent(pGame->GetMesh("Sprite"), pGame->GetMaterial("RPS")));
    pAi->GetComponent<fw::MeshComponent>()->SetUVScale(vec2(.01f, 0.01f));
    pAi->GetComponent<fw::MeshComponent>()->SetUVOffset(vec2(.3f, 0.f));
    pAi->GetTransform()->SetScale(2);
    m_Objects.push_back(pAi);

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, 3);
    Move = distr(gen);

    //pPlayer->GetComponent<fw::MeshComponent>()->SetUVScale(vec2(.33f, 1.f));
    //pPlayer->GetComponent<fw::MeshComponent>()->SetUVOffset(vec2(.66f, 0.f));
}

FinalScene::~FinalScene()
{
}

void FinalScene::StartFrame(float deltaTime)
{
    Started = true;
}

void FinalScene::OnEvent(fw::Event* pEvent)
{
    fw::Scene::OnEvent( pEvent );
}

void FinalScene::Update(float deltaTime)
{
    Scene::Update( deltaTime );

    if (Started && m_CountDown <= 0.0f)
    {
        if (m_pFramework->IsKeyDown('S'))
        {
            m_Objects[0]->GetComponent<fw::MeshComponent>()->SetUVScale(vec2(.33f, 1.f));
            m_Objects[0]->GetComponent<fw::MeshComponent>()->SetUVOffset(vec2(.66f, 0.f));
            MoveMade = RPS::Sissors;
            GameEnded = true;
        }
        else if (m_pFramework->IsKeyDown('P'))
        {
            m_Objects[0]->GetComponent<fw::MeshComponent>()->SetUVScale(vec2(.33f, 1.f));
            m_Objects[0]->GetComponent<fw::MeshComponent>()->SetUVOffset(vec2(.33f, 0.f));
            MoveMade = RPS::Paper;
            GameEnded = true;
        }
        else if (m_pFramework->IsKeyDown('R'))
        {
            m_Objects[0]->GetComponent<fw::MeshComponent>()->SetUVScale(vec2(.33f, 1.f));
            m_Objects[0]->GetComponent<fw::MeshComponent>()->SetUVOffset(vec2(.0f, 0.f));
            MoveMade = RPS::Rock;
            GameEnded = true;
        }
        if (m_pFramework->IsKeyDown('Q'))
        {
            m_Objects[0]->GetComponent<fw::MeshComponent>()->SetUVScale(vec2(.01f, 0.01f));
            m_Objects[0]->GetComponent<fw::MeshComponent>()->SetUVOffset(vec2(.3f, 0.f));
            m_Objects[1]->GetComponent<fw::MeshComponent>()->SetUVScale(vec2(.01f, 0.01f));
            m_Objects[1]->GetComponent<fw::MeshComponent>()->SetUVOffset(vec2(.3f, 0.f));
            MoveMade = RPS::None;
            AIMade = RPS::None;
            GameEnded = false;
            m_CountDown = 1.0f;
            m_Elpased = 0.0f;

            std::random_device rd; // obtain a random number from hardware
            std::mt19937 gen(rd()); // seed the generator
            std::uniform_int_distribution<> distr(1, 3);
            Move = distr(gen);
        }
    }


    if (Started && m_CountDown >= 0.0f)
    {
        m_CountDown -= deltaTime;
    }

    if (Started && m_CountDown <= 0.0f)
    {
        if(GameEnded==false)
        m_Elpased += deltaTime;
        if (Move == 1)
        {
            m_Objects[1]->GetComponent<fw::MeshComponent>()->SetUVScale(vec2(.33f, 1.f));
            m_Objects[1]->GetComponent<fw::MeshComponent>()->SetUVOffset(vec2(.66f, 0.f));
            AIMade = RPS::Sissors;
        }
        else if (Move == 2)
        {
            m_Objects[1]->GetComponent<fw::MeshComponent>()->SetUVScale(vec2(.33f, 1.f));
            m_Objects[1]->GetComponent<fw::MeshComponent>()->SetUVOffset(vec2(.33f, 0.f));
            AIMade = RPS::Paper;
        }
        else if (Move == 3)
        {
            m_Objects[1]->GetComponent<fw::MeshComponent>()->SetUVScale(vec2(.33f, 1.f));
            m_Objects[1]->GetComponent<fw::MeshComponent>()->SetUVOffset(vec2(.0f, 0.f));
            AIMade = RPS::Rock;
        }
    }

    if (GameEnded)
    {
        if (AIMade == RPS::Rock)
        {
            if (MoveMade == RPS::Rock)
            {
                Victory = false;
            }
            else if (MoveMade == RPS::Sissors)
            {
                Victory = false;
            }
            else if (MoveMade == RPS::Paper)
            {
                Victory = true;
            }
        }
        else if (AIMade == RPS::Paper)
        {
            if (MoveMade == RPS::Rock)
            {
                Victory = false;
            }
            else if (MoveMade == RPS::Sissors)
            {
                Victory = true;
            }
            else if (MoveMade == RPS::Paper)
            {
                Victory = false;
            }
        }
        else if (AIMade == RPS::Sissors)
        {
            if (MoveMade == RPS::Rock)
            {
                Victory = true;
            }
            else if (MoveMade == RPS::Sissors)
            {
                Victory = false;
            }
            else if (MoveMade == RPS::Paper)
            {
                Victory = false;
            }
        }
    }




    ImGui::Begin("Rock Paper Sissors");;
    ImGui::Text("Start Timer: %0.2f", m_CountDown);
    ImGui::Text("TimeElapsed: %0.2f", m_Elpased);

    if (GameEnded == true)
    {
        if (Victory)
        {
            Result = "VICTORY";
        }
        else
        {
            Result = "FAILURE";
        }

        
    }
    else
    {
        Result = "";
    }

    ImGui::Text(Result);

    ImGui::End();//RockPaperSissors end

}
