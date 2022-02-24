#include "Framework.h"

#include "Player.h"
#include "PlayerController.h"

Player::Player(fw::Scene* pScene, vec3 pos, PlayerController* pController)
    : GameObject("Player", pScene, pos)
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

    ////Example of is held
    //if (m_pPlayerController->IsHeld(PlayerController::Action::Right))
    //{
    //    m_pPhysicsBody->GetBody()->ApplyForceToCenter(b2Vec2(10, 0), true); //Wrapper is def built wrong apparently you pass in vec3s and the wrapper converts it to b2 stuff
    //}

    if(bOnGround)
    {
        if( m_pPlayerController->IsHeld( PlayerController::Action::Left ) )
        {
           // m_pPhysicsBody->GetBody()->ApplyForceToCenter(b2Vec2(-100, 500), true);
            m_pPhysicsBody->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(-.65f, 3), true);
            bOnGround = false;
        }
        if( m_pPlayerController->IsHeld( PlayerController::Action::Right ) )
        {
            //m_pPhysicsBody->GetBody()->ApplyForceToCenter(b2Vec2(100, 500), true);//Wrapper is def built wrong apparently you pass in vec3s and the wrapper converts it to b2 stuff
            m_pPhysicsBody->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(.65f, 3), true);
            bOnGround = false;
        }
    }

    if( m_pPlayerController->WasPressed( PlayerController::Action::Teleport ) )
    {
        m_Position = vec2( fw::Random::GetFloat( 0, 15 ), fw::Random::GetFloat( 0, 15 ) );
    }

    if( m_pSpriteSheet )
    {
        fw::SpriteSheet::SpriteInfo info = m_pSpriteSheet->GetSpriteByName( "player_06" );
        fw::MeshComponent* pMesh = GetComponent<fw::MeshComponent>();
        pMesh->SetUVScale(info.uvScale);
        pMesh->SetUVOffset(info.uvOffset);
    }
}
