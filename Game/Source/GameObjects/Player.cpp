#include "Framework.h"

#include "Player.h"
#include "PlayerController.h"

Player::Player(fw::Scene* pScene, fw::Mesh* pMesh, fw::Material* pMaterial, vec3 pos, PlayerController* pController)
    : GameObject(pScene,  pos )
    , m_pPlayerController( pController )
{
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    GameObject::Update( deltaTime );

    float speed = 5.0f;

   // vec3 newPos = m_Position;

    // Try moving up/down.
    {
        if( m_pPlayerController->IsHeld( PlayerController::Action::Up ) )
        {
           // newPos.y += speed * deltaTime;
        }
        if( m_pPlayerController->IsHeld( PlayerController::Action::Down ) )
        {
           // newPos.y -= speed * deltaTime;
        }

        
         // m_Position = newPos;

    }

    // Try moving left/right.
    {
       // newPos = m_Position;
        if( m_pPlayerController->IsHeld( PlayerController::Action::Left ) )
        {
           // newPos.x -= speed * deltaTime;
           // m_Rotation.z -= 90.0f * deltaTime;

            m_pPhysicsBody->GetBody()->ApplyForceToCenter(b2Vec2(-10, 0), true);
        }
        if( m_pPlayerController->IsHeld( PlayerController::Action::Right ) )
        {
           // newPos.x += speed * deltaTime;
            //m_Rotation.z += 90.0f * deltaTime;
            m_pPhysicsBody->GetBody()->ApplyForceToCenter(b2Vec2(10, 0), true); //Wrapper is def built wrong apparently you pass in vec3s and the wrapper converts it to b2 stuff
        }


        //m_Position = newPos;
    }

    if( m_pPlayerController->WasPressed( PlayerController::Action::Teleport ) )
    {
        m_Position = vec2( fw::Random::GetFloat( 0, 15 ), fw::Random::GetFloat( 0, 15 ) );
    }

    if( m_pSpriteSheet )
    {
        fw::SpriteSheet::SpriteInfo info = m_pSpriteSheet->GetSpriteByName( "player_06" );
        //GetComponent(fw::MeshComponent::GetStaticType())->SetUVScale(info.uvScale);
        m_pMeshComponent->SetUVScale(info.uvScale);
        m_pMeshComponent->SetUVOffset(info.uvOffset);
    }
}
