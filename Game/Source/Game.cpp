#include "Framework.h"

#include "Game.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "Meshes/Shapes.h"
#include "GameEvents/GameEvents.h"
#include "Scenes/PhysicsScene.h"

Game::Game(fw::FWCore& fwCore)
    : m_FWCore( fwCore )
{
    Init();
}

Game::~Game()
{

    delete m_pPhysicsScene;

    for( auto& it : m_Meshes )
    {
        delete it.second;
    }

    for( auto& it : m_Shaders )
    {
        delete it.second;
    }

    for( auto& it : m_Textures )
    {
        delete it.second;
    }

    for( auto& it : m_SpriteSheets )
    {
        delete it.second;
    }

    for (auto& it : m_Materials)
    {
        delete it.second;
    }

    delete m_pImGuiManager;
}

void Game::Init()
{
    m_pImGuiManager = new fw::ImGuiManager( &m_FWCore );

    // OpenGL settings.
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
    glPointSize( 10 );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    //Scene needs to access these VV
    //m_Meshes["Sprite"] = new fw::Mesh( GL_TRIANGLE_STRIP, g_SpriteVerts );
    m_Meshes["Sprite"] = new fw::Mesh( GL_TRIANGLES, g_SpriteVerts, g_SpriteIndices);
    m_Meshes["Cube"] = new fw::Mesh(GL_TRIANGLES, g_CubeVerts, g_CubeIndices);
    m_Meshes["Plane"] = CreatePlane();
    //m_Meshes["Cube"] = new fw::Mesh(GL_TRIANGLES, g_SpriteVerts, g_SpriteIndices);
    m_Shaders["Basic"] = new fw::ShaderProgram( "Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" );
    m_Textures["Sprites"] = new fw::Texture( "Data/Textures/Sprites.png" );
    m_SpriteSheets["Sprites"] = new fw::SpriteSheet( "Data/Textures/Sprites.json", m_Textures["Sprites"] );

    m_Materials["Sokoban"] = new fw::Material(m_Shaders["Basic"], m_Textures["Sprites"], fw::Color4f::Blue);

    //TODO
    //m_pCubeScene = new CubeScene(this);
    m_pPhysicsScene = new PhysicsScene(this);
    m_pCurrentScene = m_pPhysicsScene;

    //// ^^ Replaces
    //{

    //}
}

void Game::StartFrame(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );
    
    m_pCurrentScene->StartFrame(deltaTime);

}

void Game::OnEvent(fw::Event* pEvent)
{

    m_pCurrentScene->OnEvent(pEvent);

}

void Game::Update(float deltaTime)
{
    ImGui::ShowDemoWindow();

   m_pCurrentScene->Update(deltaTime);

}

void Game::Draw()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    m_pCurrentScene->Draw();

    //m_pPlayerController->OnEvent(pEvent);
    
    m_pImGuiManager->EndFrame();
}
