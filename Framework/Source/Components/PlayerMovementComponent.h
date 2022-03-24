#pragma once

#include "Component.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"

class PlayerController;

namespace fw {

class PlayerMovementComponent : public Component
{
public:
    PlayerMovementComponent(PlayerController* pController, GameObject* pGameObject);
    virtual ~PlayerMovementComponent();

    static const char* GetStaticType() { return "PlayerMovementComponent"; }
    virtual const char* GetType() override { return GetStaticType(); }

    void Update(float deltaTime);


protected:
    PlayerController* m_pPlayerController;
    GameObject* m_pGameObject;
    float m_Speed;

};

} // namespace fw
