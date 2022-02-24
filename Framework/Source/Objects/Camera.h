#pragma once

#include "GameObject.h"

namespace fw {

 class Scene;

class Camera : public GameObject
{
public:
    Camera(Scene* pScene, vec3 pos, vec3 lookAt, float FOVDeg);
    virtual ~Camera();

    virtual void Update(float deltaTime) override;

    // Getters.
    MyMatrix GetProjectionMatrix() { return m_ProjMat; }
    MyMatrix GetViewMatrix() { return m_ViewMat; }

    // Setters.
    void SetObjectWeAreFollowing(GameObject* pObj) { m_pObjectWeAreFollowing = pObj; }

    bool CameraShake(float DeltaTime);

protected:
    
    GameObject* m_pObjectWeAreFollowing = nullptr;

    MyMatrix m_ViewMat;
    MyMatrix m_ProjMat;

    float ShakeTime;
    vec3 StartLocation;

    vec3 m_LookAtPoint;
};

} // namespace fw
