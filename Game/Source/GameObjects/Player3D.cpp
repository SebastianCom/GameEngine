#include "Framework.h"

#include "Player3D.h"
#include "PlayerController.h"

Player3D::Player3D(fw::Scene* pScene, vec3 pos, PlayerController* pController)
    : GameObject( "Player", pScene, pos )
    , m_pPlayerController( pController )
{
}

Player3D::~Player3D()
{
}

void Player3D::Update(float deltaTime)
{
    GameObject::Update( deltaTime );

    float speed = 5.0f;

    vec3 newPos = m_pTransform->GetPosition();

    // Setup movement axes.
    float forwardAxis = 0;
    float rightAxis = 0;
    if( m_pPlayerController->IsHeld( PlayerController::Action::Up ) ) { forwardAxis += 1; }
    if( m_pPlayerController->IsHeld( PlayerController::Action::Down ) ) { forwardAxis -= 1; }
    if( m_pPlayerController->IsHeld( PlayerController::Action::Left ) ) { rightAxis -= 1; }
    if( m_pPlayerController->IsHeld( PlayerController::Action::Right ) ) { rightAxis += 1; }

    if( m_pPhysicsBody )
    {
        // Get camera forward and right vectors.
        float camY = (m_pScene->GetCamera()->GetTransform()->GetRotation().y + 90) / 180.0f * PI;
        vec3 forwardDir(cos(camY), 0, sin(camY));
        vec3 rightDir(cos(camY - PI / 2), 0, sin(camY - PI / 2));

        vec3 dir = forwardDir * forwardAxis + rightDir * rightAxis;
        dir.Normalize();

        // Move the player.
        newPos += dir * speed * deltaTime;
        m_pPhysicsBody->GetBody()->ApplyForceToCenter(dir * speed);
    }
    else
    {
        // Get camera forward and right vectors.
        float camY = (m_pScene->GetCamera()->GetTransform()->GetRotation().y + 90) / 180.0f * PI;
        vec3 forwardDir( cos(camY), 0, sin(camY) );
        vec3 rightDir( cos(camY-PI/2), 0, sin(camY-PI/2) );

        vec3 dir = forwardDir * forwardAxis + rightDir * rightAxis;
        dir.Normalize();

        // Move the player.
        newPos += dir * speed * deltaTime;
    
        m_pTransform->SetRotation( vec3( 0, m_pScene->GetCamera()->GetTransform()->GetRotation().y, 0 ) );
    }

    // Teleport the player.
    if( m_pPlayerController->WasPressed( PlayerController::Action::Teleport ) )
    {
        newPos = vec2( fw::Random::GetFloat( 0, 15 ), fw::Random::GetFloat( 0, 15 ) );
    }

    m_pTransform->SetPosition( newPos );

    if( m_pSpriteSheet )
    {
        fw::SpriteSheet::SpriteInfo info = m_pSpriteSheet->GetSpriteByName( "player_06" );

        fw::MeshComponent* pMesh = GetComponent<fw::MeshComponent>();
        pMesh->SetUVScale( info.uvScale );
        pMesh->SetUVOffset( info.uvOffset );
    }
}
