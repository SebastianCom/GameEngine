#include "CoreHeaders.h"

#include "PlayerMovementComponent.h"
#include "GameObjects/PlayerController.h"
#include "Objects/GameObject.h"

namespace fw {

PlayerMovementComponent::PlayerMovementComponent(PlayerController* pController, GameObject* pGameObject)
	:m_pPlayerController(pController)
    , m_pGameObject(pGameObject)
{
    m_Speed = 5.0f;
}

PlayerMovementComponent::~PlayerMovementComponent()
{
}

void PlayerMovementComponent::Update(float deltaTime)
{
    
    m_pGameObject->Update(deltaTime);

    

    vec3 newPos = m_pGameObject->GetTransform()->GetPosition();

    // Setup movement axes.
    float forwardAxis = 0;
    float rightAxis = 0;
    if (m_pPlayerController->IsHeld(PlayerController::Action::Up)) { forwardAxis += 1; }
    if (m_pPlayerController->IsHeld(PlayerController::Action::Down)) { forwardAxis -= 1; }
    if (m_pPlayerController->IsHeld(PlayerController::Action::Left)) { rightAxis -= 1; }
    if (m_pPlayerController->IsHeld(PlayerController::Action::Right)) { rightAxis += 1; }

    if (m_pGameObject->GetPhysicsBody())
    {
        m_pGameObject->GetPhysicsBody()->GetBody()->ApplyForceToCenter(vec3(rightAxis, forwardAxis, 0) * m_Speed);
    }
    else
    {
        // Get camera forward and right vectors.
        float camY = (m_pGameObject->GetScene()->GetCamera()->GetTransform()->GetRotation().y + 90) / 180.0f * PI;
        vec3 forwardDir(cos(camY), 0, sin(camY));
        vec3 rightDir(cos(camY - PI / 2), 0, sin(camY - PI / 2));

        vec3 dir = forwardDir * forwardAxis + rightDir * rightAxis;
        dir.Normalize();

        // Move the player.
        newPos += dir * m_Speed * deltaTime;

        m_pGameObject->GetTransform()->SetRotation(vec3(0, m_pGameObject->GetScene()->GetCamera()->GetTransform()->GetRotation().y, 0));
    }

    // Teleport the player.
    if (m_pPlayerController->WasPressed(PlayerController::Action::Teleport))
    {
        newPos = vec2(fw::Random::GetFloat(0, 15), fw::Random::GetFloat(0, 15));
    }

    m_pGameObject->GetTransform()->SetPosition(newPos);

    //if (m_pSpriteSheet)
    //{
    //    fw::SpriteSheet::SpriteInfo info = m_pSpriteSheet->GetSpriteByName("player_06");

    //    fw::MeshComponent* pMesh = GetComponent<fw::MeshComponent>();
    //    pMesh->SetUVScale(info.uvScale);
    //    pMesh->SetUVOffset(info.uvOffset);
    //}
}


} // namespace fw
