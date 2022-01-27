#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "Objects/GameObject.h"

class PlayerController;

class Player : public fw::GameObject
{
public:
    Player(fw::GameCore* pGame, fw::Mesh* pMesh, fw::Material* pMaterial, vec2 pos, PlayerController* pController);
    virtual ~Player();

    virtual void Update(float deltaTime) override;
    //virtual void Draw() override;

    // Setters.
    void SetSpriteSheet(fw::SpriteSheet* pSpriteSheet) { m_pSpriteSheet = pSpriteSheet; }

protected:
    PlayerController* m_pPlayerController = nullptr;

    fw::SpriteSheet* m_pSpriteSheet = nullptr;
};
