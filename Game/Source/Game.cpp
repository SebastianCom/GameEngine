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
#include "Scenes/LightScene.h"
#include "Scenes/ObjScene.h"
#include "Scenes/CubeMap.h"
#include "Scenes/Assignment2Scene.h"


//Working Copy for maintenance 2 - needed a comment to i could commit again
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
    //glViewport( 300, 50, 600, 600 );

    // Back-face culling settings.
    glEnable( GL_CULL_FACE );
    //glCullFace( GL_BACK );
    glFrontFace( GL_CW );

    //Create a framebuffer object
    m_pOffscreenFBO = new fw::FrameBufferObject(400, 400, { fw::FrameBufferObject::FBOColorFormat_RGBA_UByte });

    // Load our Meshes.
    m_Meshes["Sprite"] = new fw::Mesh( GL_TRIANGLES, g_SpriteVerts, g_SpriteIndices );
    m_Meshes["Cube"] = new fw::Mesh( GL_TRIANGLES, g_CubeVerts);
    m_Meshes["Plane"] = CreatePlane();
    m_Meshes["Obj"] = new fw::Mesh("Data/Meshes/cube.obj");
    m_Meshes["ObjGun"] = new fw::Mesh("Data/Meshes/Sebs_Glock3.obj");
    m_Meshes["ObjTree"] = new fw::Mesh("Data/Meshes/Tree_NotbySeb.obj");
    m_Meshes["Sphere"] = new fw::Mesh("Data/Meshes/sphere.obj");

    // Load our Shaders.
    m_Shaders["Basic"] = new fw::ShaderProgram( "Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" );
    m_Shaders["Water"] = new fw::ShaderProgram( "Data/Shaders/Water.vert", "Data/Shaders/Water.frag" );
    m_Shaders["LitColor"] = new fw::ShaderProgram("Data/Shaders/Light-SolidColor.vert", "Data/Shaders/Light-SolidColor.frag");
    m_Shaders["Cubemap"] = new fw::ShaderProgram("Data/Shaders/CubeMap.vert", "Data/Shaders/CubeMap.frag");

    // Load our Textures.
    m_Textures["Sprites"] = new fw::Texture( "Data/Textures/Sprites.png" );
    m_Textures["Water"] = new fw::Texture( "Data/Textures/Water.png" );
    m_Textures["BG"] = new fw::Texture( "Data/Textures/BG.png" );
    m_Textures["BaseColor"] = new fw::Texture(255, 165, 0, 255); 
    m_Textures["Red"] = new fw::Texture("Data/Textures/Color/Red.png"); 
    m_Textures["Yellow"] = new fw::Texture("Data/Textures/Color/Yellow.png"); 
    m_Textures["Blue"] = new fw::Texture("Data/Textures/Color/Blue.png"); 
    m_Textures["Brown"] = new fw::Texture("Data/Textures/Color/Brown.png"); 
    m_Textures["Green"] = new fw::Texture("Data/Textures/Color/Green.png"); 
    m_Textures["LightBlue"] = new fw::Texture("Data/Textures/Color/LightBlue.png"); 
    m_Textures["Orange"] = new fw::Texture("Data/Textures/Color/Orange.png"); 
    m_Textures["Pink"] = new fw::Texture("Data/Textures/Color/Pink.png"); 
    m_Textures["Purple"] = new fw::Texture("Data/Textures/Color/Purple.png"); 
    m_Textures["White"] = new fw::Texture("Data/Textures/Color/White.png"); 
    m_Textures["TestCubeMap"] = new fw::Texture({ "Data/Textures/TestCubeMap/posx.png", 
                                                  "Data/Textures/TestCubeMap/negx.png",
                                                  "Data/Textures/TestCubeMap/posy.png", 
                                                  "Data/Textures/TestCubeMap/negy.png", 
                                                  "Data/Textures/TestCubeMap/posz.png", 
                                                  "Data/Textures/TestCubeMap/negz.png" });
    m_Textures["Yokohama"] = new fw::Texture({ "Data/Textures/Yokohama2/posx.png",
                                              "Data/Textures/Yokohama2/negx.png",
                                              "Data/Textures/Yokohama2/posy.png",
                                              "Data/Textures/Yokohama2/negy.png",
                                              "Data/Textures/Yokohama2/posz.png",
                                              "Data/Textures/Yokohama2/negz.png" });

    // Create our Materials.
    m_Materials["Sprites"] = new fw::Material( m_Shaders["Basic"], m_Textures["Sprites"], fw::Color4f::Blue());
    m_Materials["Water"] = new fw::Material( m_Shaders["Water"], m_Textures["Water"], fw::Color4f::Blue());
    m_Materials["BG"] = new fw::Material( m_Shaders["Basic"], m_Textures["BG"], fw::Color4f::Blue() );
    m_Materials["LitMat"] = new fw::Material(m_Shaders["LitColor"], nullptr, fw::Color4f::White());
    m_Materials["CubeMap"] = new fw::Material( m_Shaders["Cubemap"], nullptr, fw::Color4f::Blue(), m_Textures["TestCubeMap"]);
    m_Materials["Yokohama"] = new fw::Material( m_Shaders["Cubemap"], nullptr, fw::Color4f::Blue(), m_Textures["Yokohama"]);
    
    //Color Mats
    m_Materials["Purple"] = new fw::Material( m_Shaders["Basic"], m_Textures["Purple"], fw::Color4f::Blue() );
    m_Materials["White"] = new fw::Material( m_Shaders["Basic"], m_Textures["White"], fw::Color4f::Blue() );
    m_Materials["LightBlue"] = new fw::Material( m_Shaders["Basic"], m_Textures["LightBlue"], fw::Color4f::Blue() );
    m_Materials["Red"] = new fw::Material( m_Shaders["Basic"], m_Textures["Red"], fw::Color4f::Blue() );
    m_Materials["Pink"] = new fw::Material( m_Shaders["Basic"], m_Textures["Pink"], fw::Color4f::Blue() );

    // Load our Spritesheets.
    m_SpriteSheets["Sprites"] = new fw::SpriteSheet( "Data/Textures/Sprites.json", m_Textures["Sprites"] );

    // Create our Scenes.
    m_Scenes["Obj"] = new ObjScene( this );
    m_Scenes["Cube"] = new CubeScene( this );
    m_Scenes["Physics"] = new PhysicsScene( this );
    m_Scenes["Physics3D"] = new PhysicsScene3D( this );
    m_Scenes["ThirdPerson"] = new ThirdPersonScene( this );
    m_Scenes["Water"] = new WaterScene( this );
    m_Scenes["Light"] = new LightScene( this );
    m_Scenes["CubeMap"] = new CubemapScene( this );
    m_Scenes["A2"] = new Assignment2Scene( this );
    m_pCurrentScene = m_Scenes["A2"];
}

void Game::StartFrame(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDocking;

    flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::Begin("Main Dock", nullptr, flags);
    ImGui::DockSpace(ImGui::GetID("Game Dockspace"));
    ImGui::End();//Main dock

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
    if( ImGui::Button( "Obj" ) )
    {
        m_pCurrentScene = m_Scenes["Obj"];
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
    if (ImGui::Button("Physics3D"))
    {
        m_pCurrentScene = m_Scenes["Physics3D"];
    }
    if (ImGui::Button("Light"))
    {
        m_pCurrentScene = m_Scenes["Light"];
    }
    if (ImGui::Button("Cube"))
    {
        m_pCurrentScene = m_Scenes["Cube"];
    }
    if (ImGui::Button("CubeMap"))
    {
        m_pCurrentScene = m_Scenes["CubeMap"];
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

        ImGui::Begin("Debug");
        ImGui::Text( "Window Coords: %d, %d", windowCoord.x, windowCoord.y );
        ImGui::Text( "Viewport Coords: %d, %d", viewportCoord.x, viewportCoord.y );
        ImGui::Text( "Clip Space Coords: %0.2f, %0.2f", clipSpaceCoord.x, clipSpaceCoord.y );
        ImGui::Text( "View Space Coords: %0.2f, %0.2f", viewSpaceCoord.x, viewSpaceCoord.y );
        ImGui::Text( "World Space at Z zero:  %0.2f, %0.2f, %0.2f", posAtZZero.x, posAtZZero.y, posAtZZero.z );
        ImGui::Text( "World Space at desized: %0.2f, %0.2f, %0.2f", posAtZDesired.x, posAtZDesired.y, posAtZDesired.z );
        ImGui::End(); //Debug
    }

}

void Game::Draw()
{
    //Offscreen
    m_pOffscreenFBO->Bind();
    glViewport(0, 0, m_pOffscreenFBO->GetRequestedWidth(), m_pOffscreenFBO->GetRequestedHeight());
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    //Skybox
    {
        glDepthMask(false);
        glFrontFace(GL_CCW);

        fw::mat4 identity;
        identity.SetIdentity();
        m_Meshes["Cube"]->Draw(m_pCurrentScene->GetCamera(), m_Shaders["Cubemap"], m_Textures["Yokohama"], identity, identity, vec2(1, 1), vec2(1, 1), 0.0f, m_Materials["Yokohama"]);

        glDepthMask(true);
        glFrontFace(GL_CW);
    }
    
    m_pCurrentScene->Draw();
    m_pOffscreenFBO->Unbind();

    //Onscreen 
    glViewport(0, 0, 1280, 720);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    ImGui::Begin("Scene");

    ImVec2 windowMin = ImGui::GetWindowContentRegionMin();
    ImVec2 windowMax = ImGui::GetWindowContentRegionMax();
    ImVec2 windowSize(windowMax.x - windowMin.x, windowMax.y - windowMin.y);

    m_pOffscreenFBO->Resize(windowSize.x, windowSize.y);
    m_pCurrentScene->ResizeCamera(windowSize.x, windowSize.y);

    ImTextureID textureID = (ImTextureID)(uint64_t)m_pOffscreenFBO->GetColorTextureHandle(0);
    ImVec2 uv0 = ImVec2(0, m_pOffscreenFBO->GetHeightRatio());
    ImVec2 uv1 = ImVec2(m_pOffscreenFBO->GetWidthRatio(), 0);
    ImGui::Image(textureID, windowSize, uv0, uv1);
    ImGui::End();
    
    m_pImGuiManager->EndFrame();
}
