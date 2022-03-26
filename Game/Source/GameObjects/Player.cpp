#include "Framework.h"

#include "Player.h"
#include "PlayerController.h"

Player::Player(fw::Scene* pScene, vec3 pos, PlayerController* pController)
    : GameObject( "Player", pScene, pos )
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

    vec3 newPos = m_pTransform->GetPosition();


    // Teleport the player.
    if (m_pPlayerController->WasPressed(PlayerController::Action::Teleport))
    {
        newPos = vec2(fw::Random::GetFloat(0, 15), fw::Random::GetFloat(0, 15));
    }

    m_pTransform->SetPosition(newPos);

    if (m_pSpriteSheet)
    {
        fw::SpriteSheet::SpriteInfo info = m_pSpriteSheet->GetSpriteByName("player_06");

        fw::MeshComponent* pMesh = GetComponent<fw::MeshComponent>();
        pMesh->SetUVScale(info.uvScale);
        pMesh->SetUVOffset(info.uvOffset);
    }
}
