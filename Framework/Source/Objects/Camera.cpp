#include "CoreHeaders.h"

#include "Camera.h"
#include "Scene.h"
#include "Math/Random.h"

namespace fw {

Camera::Camera(Scene* pScene, vec3 pos, vec3 lookAt, float FOVDeg)
    : GameObject("Camera", pScene, pos)
{
    m_Position = pos;
    m_ViewMat.CreateLookAtView(m_Position, vec3(0, 1, 0), lookAt);
    m_ProjMat.CreatePerspectiveVFoV(FOVDeg, 1.0f, 0.01f, 1000.0f);
    ShakeTime = .05f;
    m_LookAtPoint = lookAt;
}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
    m_Position = m_pObjectWeAreFollowing->GetPosition() -  vec3(0,0,-20);
}

bool Camera::CameraShake(float DeltaTime)
{
    if (ShakeTime == .05f)
    {
        StartLocation = m_LookAtPoint;
    }

    if (ShakeTime > 0)
    {
        vec3 RandPos = vec3(m_LookAtPoint.x = fw::Random::GetFloat(-.5f, .5f), m_LookAtPoint.y = fw::Random::GetFloat(-.5f, .5f), 0);
        m_ViewMat.CreateLookAtView(m_Position, vec3(0, 1, 0), RandPos);
        ShakeTime -= DeltaTime;
        return true;
    }
    else
    {
        ShakeTime = .05f;
        m_ViewMat.CreateLookAtView(m_Position, vec3(0, 1, 0), StartLocation);
        m_LookAtPoint = StartLocation;
        return false;
    }



}

} // namespace fw
