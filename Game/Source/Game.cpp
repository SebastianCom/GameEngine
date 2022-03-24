#include "Framework.h"

#include "Game.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "Meshes/Shapes.h"
#include "GameEvents/GameEvents.h"
#include "Scenes/CubeScene.h"
#include "Scenes/PhysicsScene.h"
#include "Scenes/PhysicsScene3D.h"
#include "Scenes/ThirdPersonScene.h"
#include "Scenes/WaterScene.h"

Game::Game(fw::FWCore& fwCore)
    : m_FWCore( fwCore )
{
    Init();
}

Game::~Game()
{
    m_FWCore.GetEventManager()->UnregisterForEvents( fw::InputEvent::GetStaticEventType(), this );

    for( auto& it : m_Scenes )
    {
        delete it.second;
    }

    for( auto& it : m_Materials )
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

    delete m_pImGuiManager;
}

void Game::Init()
{
    m_FWCore.GetEventManager()->RegisterForEvents( fw::InputEvent::GetStaticEventType(), this );

    m_pImGuiManager = new fw::ImGuiManager( &m_FWCore );

    // OpenGL settings.
    glClearColor( 0.0f, 0.0f, 0.2f, 1.0f );
    glPointSize( 10 );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable( GL_DEPTH_TEST );
    glViewport( 300, 50, 600, 600 );

    // Back-face culling settings.
    glEnable( GL_CULL_FACE );
    //glCullFace( GL_BACK );
    glFrontFace( GL_CW );

    // Load our Meshes.
    m_Meshes["Sprite"] = new fw::Mesh( GL_TRIANGLES, g_SpriteVerts, g_SpriteIndices );
    m_Meshes["Cube"] = new fw::Mesh( GL_TRIANGLES, g_CubeVerts );
    m_Meshes["Plane"] = CreatePlane();

    // Load our Shaders.
    m_Shaders["Basic"] = new fw::ShaderProgram( "Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" );
    m_Shaders["Water"] = new fw::ShaderProgram( "Data/Shaders/Water.vert", "Data/Shaders/Water.frag" );

    // Load our Textures.
    m_Textures["Sprites"] = new fw::Texture( "Data/Textures/Sprites.png" );
    m_Textures["Water"] = new fw::Texture( "Data/Textures/Water.png" );
    m_Textures["BG"] = new fw::Texture( "Data/Textures/BG.png" );

    // Create our Materials.
    m_Materials["Sprites"] = new fw::Material( m_Shaders["Basic"], m_Textures["Sprites"], fw::Color4f::Blue() );
    m_Materials["Water"] = new fw::Material( m_Shaders["Water"], m_Textures["Water"], fw::Color4f::Blue() );
    m_Materials["BG"] = new fw::Material( m_Shaders["Basic"], m_Textures["BG"], fw::Color4f::Blue() );

    // Load our Spritesheets.
    m_SpriteSheets["Sprites"] = new fw::SpriteSheet( "Data/Textures/Sprites.json", m_Textures["Sprites"] );

    // Load our Materials (which I didn't implement!!!).
    //m_Materials["Sokoban"] = new fw::Material( m_Shaders["Basic"], m_Textures["Sprites"], fw::Color4f::Blue() );

    // Create our Scenes.
    m_Scenes["Cube"] = new CubeScene( this );
    m_Scenes["Physics"] = new PhysicsScene( this );
    m_Scenes["Physics3D"] = new PhysicsScene3D( this );
    m_Scenes["ThirdPerson"] = new ThirdPersonScene( this );
    m_Scenes["Water"] = new WaterScene( this );
    m_pCurrentScene = m_Scenes["Physics3D"];
}

void Game::StartFrame(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );

    m_pCurrentScene->StartFrame( deltaTime );
}

void Game::OnEvent(fw::Event* pEvent)
{
    m_pCurrentScene->OnEvent( pEvent );
}

void Game::Update(float deltaTime)
{
    ImGui::ShowDemoWindow();

    ImGui::Begin( "Scene Selector" );
    if( ImGui::Button( "Cube" ) )
    {
        m_pCurrentScene = m_Scenes["Cube"];
    }
    if( ImGui::Button( "Physics" ) )
    {
        m_pCurrentScene = m_Scenes["Physics"];
    }
    if( ImGui::Button( "ThirdPerson" ) )
    {
        m_pCurrentScene = m_Scenes["ThirdPerson"];
    }
    if( ImGui::Button( "Water" ) )
    {
        m_pCurrentScene = m_Scenes["Water"];
    }
    ImGui::End(); //"Scene Selector"

    m_pCurrentScene->Update( deltaTime );

    // Figure out world space coordinate of mouse.
    {
        // Get window mouse coordinates.
        ivec2 windowCoord;
        m_FWCore.GetMouseCoordinates( &windowCoord.x, &windowCoord.y );

        // Convert into opengl "viewport" coordinates.
        //glViewport( 300, 50, 600, 600 );
        // TODO: Make these actual member variables:
        ivec2 windowSize( m_FWCore.GetWindowWidth(), m_FWCore.GetWindowHeight() );
        ivec2 m_ViewportPos( 300, 50 );
        ivec2 m_ViewportSize( 600, 600 );

        ivec2 viewportCoord;
        viewportCoord.x = windowCoord.x - m_ViewportPos.x;
        viewportCoord.y = windowSize.y - windowCoord.y - m_ViewportPos.y;

        // Convert into clip space coordinates.
        vec2 clipSpaceCoord = viewportCoord / (m_ViewportSize/2.0f) - 1.0f;

        vec4 clipSpaceCoord4 = vec4( clipSpaceCoord, 1, 1 );
        // Convert into view space coordinates.
        fw::mat4 invProj = m_pCurrentScene->GetCamera()->GetProjectionMatrix().GetInverse();        
        vec4 viewSpaceCoord = invProj * clipSpaceCoord4;

        // Convert into world space coordinates.
        fw::mat4 invView = m_pCurrentScene->GetCamera()->GetViewMatrix().GetInverse();        
        vec4 worldSpaceCoord = invView * viewSpaceCoord;

        vec3 nearPosition = m_pCurrentScene->GetCamera()->GetTransform()->GetPosition();
        vec3 farPosition = worldSpaceCoord.XYZ() / worldSpaceCoord.w;

        float zZero = 0.0f;
        vec3 rayDir = farPosition - nearPosition;
        float rayPerc = (zZero - nearPosition.z) / rayDir.z;
        vec3 posAtZZero = nearPosition + rayDir*rayPerc;

        float zDesired = 10.0f;
        rayPerc = (zDesired - nearPosition.z) / rayDir.z;
        vec3 posAtZDesired = nearPosition + rayDir*rayPerc;

        ImGui::Text( "Window Coords: %d, %d", windowCoord.x, windowCoord.y );
        ImGui::Text( "Viewport Coords: %d, %d", viewportCoord.x, viewportCoord.y );
        ImGui::Text( "Clip Space Coords: %0.2f, %0.2f", clipSpaceCoord.x, clipSpaceCoord.y );
        ImGui::Text( "View Space Coords: %0.2f, %0.2f", viewSpaceCoord.x, viewSpaceCoord.y );
        ImGui::Text( "World Space at Z zero:  %0.2f, %0.2f, %0.2f", posAtZZero.x, posAtZZero.y, posAtZZero.z );
        ImGui::Text( "World Space at desized: %0.2f, %0.2f, %0.2f", posAtZDesired.x, posAtZDesired.y, posAtZDesired.z );
    }
}

void Game::Draw()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    m_pCurrentScene->Draw();

    m_pImGuiManager->EndFrame();
}
