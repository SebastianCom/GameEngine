#include "CoreHeaders.h"

#include "Camera.h"
#include "Scene.h"

namespace fw {

Camera::Camera(Scene* pScene, vec3 pos, vec3 lookAt, float FOVDeg)
    : GameObject(pScene, pos )
{
    m_Position = pos;
    m_ViewMat.CreateLookAtView(m_Position, vec3(0, 1, 0), lookAt);
    m_ProjMat.CreatePerspectiveVFoV(FOVDeg, 1.0f, 0.01f, 1000.0f);
}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
    m_Position = m_pObjectWeAreFollowing->GetPosition() -  vec3(0,0,-20);
}

} // namespace fw
