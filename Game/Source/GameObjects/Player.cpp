#include "Framework.h"

#include "Player.h"
#include "PlayerController.h"

Player::Player(fw::GameCore* pGame, fw::Mesh* pMesh, fw::Material* pMaterial, vec2 pos, PlayerController* pController)
    : GameObject( pGame, pMesh, pMaterial, pos )
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

    vec2 newPos = m_Position;

    // Try moving up/down.
    {
        if( m_pPlayerController->IsHeld( PlayerController::Action::Up ) )
        {
            newPos.y += speed * deltaTime;
        }
        if( m_pPlayerController->IsHeld( PlayerController::Action::Down ) )
        {
            newPos.y -= speed * deltaTime;
        }

        
         // m_Position = newPos;

    }

    // Try moving left/right.
    {
        newPos = m_Position;
        if( m_pPlayerController->IsHeld( PlayerController::Action::Left ) )
        {
            newPos.x -= speed * deltaTime;
        }
        if( m_pPlayerController->IsHeld( PlayerController::Action::Right ) )
        {
            newPos.x += speed * deltaTime;
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
        m_UVScale = info.uvScale;
        m_UVOffset = info.uvOffset;
    }
}
