#include "CoreHeaders.h"

#include "Camera.h"
#include "Scene.h"

namespace fw {

Camera::Camera(Scene* pScene, vec2 pos, vec2 projScale)
    : GameObject(pScene, pos )
    , m_ProjectionScale( projScale )
{
}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
    m_Position = m_pObjectWeAreFollowing->GetPosition();
}

} // namespace fw
