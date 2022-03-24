#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "Objects/GameObject.h"

class PlayerController;

class Player3D : public fw::GameObject
{
public:
    Player3D(fw::Scene* pScene, vec3 pos, PlayerController* pController);
    virtual ~Player3D();

    virtual void Update(float deltaTime) override;
    //virtual void Draw() override;

    // Setters.
    void SetSpriteSheet(fw::SpriteSheet* pSpriteSheet) { m_pSpriteSheet = pSpriteSheet; }

protected:
    PlayerController* m_pPlayerController = nullptr;

    fw::SpriteSheet* m_pSpriteSheet = nullptr;
};
