#include "Framework.h"

#include "Game.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "Meshes/Shapes.h"
#include "GameEvents/GameEvents.h"
#include "Scenes/PhysicsScene.h"
#include "Scenes/WaterScene.h"
#include "Scenes/CubeScene.h"

Game::Game(fw::FWCore& fwCore)
    : m_FWCore( fwCore )
{
    Init();
}

Game::~Game()
{

    for (auto& it : m_Scenes)
    {
        delete it.second;
    }

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
    // TODO
    m_GridSize = vec2(5, 5);
    m_WorldSize = vec3(10, 10, 10);
    m_Meshes["Plane"] = CreatePlane(m_GridSize, m_WorldSize);
    m_OldGridSize = m_GridSize;
    m_OldWorldSize = m_WorldSize;
    //m_Meshes["Cube"] = new fw::Mesh(GL_TRIANGLES, g_SpriteVerts, g_SpriteIndices);
    m_Shaders["Basic"] = new fw::ShaderProgram( "Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" );
    m_Shaders["Water"] = new fw::ShaderProgram( "Data/Shaders/Water.vert", "Data/Shaders/Water.frag" );
    m_Textures["Sprites"] = new fw::Texture( "Data/Textures/Sprites.png" );
    m_Textures["BaseColor"] = new fw::Texture(255, 165, 0, 255, 0, 150, 255,255);
    m_Textures["Water"] = new fw::Texture("Data/Textures/Water.png");
    m_SpriteSheets["Sprites"] = new fw::SpriteSheet( "Data/Textures/Sprites.json", m_Textures["Sprites"] );

    m_Materials["Sokoban"] = new fw::Material(m_Shaders["Basic"], m_Textures["Sprites"], fw::Color4f::Blue);
    m_Materials["BaseColor"] = new fw::Material(m_Shaders["Basic"], m_Textures["BaseColor"], fw::Color4f::Black);
    m_Materials["Water"] = new fw::Material(m_Shaders["Water"], m_Textures["Water"], fw::Color4f::WaterBlue);
    
    
    m_Scenes["Physics"] = new PhysicsScene(this);
    m_Scenes["Cube"] = new CubeScene(this);
    m_Scenes["Water"] = new WaterScene(this);


    m_pCurrentScene = m_Scenes["Water"];

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

   SwitchScene();

   if(m_pCurrentScene == m_Scenes["Water"])
   ChangeWindowSize();

   m_pCurrentScene->Update(deltaTime);

}

void Game::SwitchScene()
{
    if (ImGui::Button("Physics Scene"))
    {
        delete m_Scenes["Physics"];
        m_Scenes["Physics"] = new PhysicsScene(this);
        m_pCurrentScene = m_Scenes["Physics"];
    }
    if (ImGui::Button("Cube Scene"))
        m_pCurrentScene = m_Scenes["Cube"];
    if (ImGui::Button("Water Scene"))
    {
        m_pCurrentScene = m_Scenes["Water"];
    }
}

void Game::ChangeWindowSize()
{
    static int GridImguiX = { int(m_GridSize.x) };
    static int GridImguiY = { int(m_GridSize.y) };
    ImGui::InputInt("Grid X", &GridImguiX, 1);
    ImGui::InputInt("Grid Y", &GridImguiY, 1);
    if (GridImguiX >= 0)
        m_GridSize.x = GridImguiX;
    if(GridImguiY >=0)
        m_GridSize.y = GridImguiY;

    static int WorldImguiX = { int(m_WorldSize.x) };
    static int WorldImguiY = { int(m_WorldSize.z) };
    ImGui::InputInt("World X", &WorldImguiX, 1);
    ImGui::InputInt("World Z", &WorldImguiY, 1);
    if (WorldImguiX >= 0)
        m_WorldSize.x = WorldImguiX;
    if (WorldImguiY >= 0)
        m_WorldSize.z = WorldImguiY;

    if (m_GridSize != m_OldGridSize || m_WorldSize != m_OldWorldSize)
    {
        delete m_Meshes["Plane"];
        m_Meshes["Plane"] = CreatePlane(m_GridSize, m_WorldSize);

        //Alright So here is the deal, i know this is bad. I know i shouldnt have to do this. However with the current set up and 
        //components i really struggled here. My grid would only draw a third of the time when making changes unless i reset the scene
        //i tried many things to combat this and ultimatley wasted way too much time. This is function so it will last as a place holder for now.
        delete m_Scenes["Water"];
        m_Scenes["Water"] = new WaterScene(this);
        m_pCurrentScene = m_Scenes["Water"];
        m_OldGridSize = m_GridSize;
        m_OldWorldSize = m_WorldSize;
    }
}

void Game::Draw()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    m_pCurrentScene->Draw();

    //m_pPlayerController->OnEvent(pEvent);
    
    m_pImGuiManager->EndFrame();
}


