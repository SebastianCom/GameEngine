#pragma once

#include "GameObject.h"

namespace fw {

class FWCore;

class Camera : public GameObject
{
public:
    Camera(Scene* pScene, vec3 pos);
    virtual ~Camera();

    virtual void Update(float deltaTime) override;
    void Hack_ThirdPersonCamUpdate(FWCore* pFramework, float deltaTime);

    // Getters.
    mat4& GetViewMatrix() { return m_ViewMatrix; }
    mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }

    // Setters.
    void SetLookAtPosition(vec3 pos) { m_LookAtPosition = pos; }
    void SetObjectWeAreLookingAt(GameObject* pObj) { m_pObjectWeAreLookingAt = pObj; }

    void SetRatio(float ratio) { AspectRatio = ratio; }

protected:
    mat4 m_ViewMatrix;
    mat4 m_ProjectionMatrix;

    float AspectRatio = 1.0f;

    vec3 m_LookAtPosition = vec3(0,0,0);
    GameObject* m_pObjectWeAreLookingAt = nullptr;
};

} // namespace fw
