#include "CoreHeaders.h"

#include "Camera.h"
#include "Objects/Scene.h"
#include "Components/TransformComponent.h"
#include "FWCore.h"

namespace fw {

Camera::Camera(Scene* pScene, vec3 pos)
    : GameObject( "Camera", pScene, pos )
{
}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
    if( m_pObjectWeAreLookingAt )
    {
        m_LookAtPosition = m_pObjectWeAreLookingAt->GetTransform()->GetPosition();
    }

    m_ViewMatrix.CreateLookAtView( GetTransform()->GetPosition(), vec3(0,1,0), m_LookAtPosition );
    m_ProjectionMatrix.CreatePerspectiveVFoV( 45.0f, 1.0f, 0.01f, 400.0f );
    //m_ProjectionMatrix.CreateOrtho( -5, 5,   -5, 5,   -25, 25 );
}

void Camera::Hack_ThirdPersonCamUpdate(FWCore* pFramework, float deltaTime)
{
    float speed = 90.0f;
    float distance = 10.0f;

    vec3 rot = GetTransform()->GetRotation();

    if( pFramework->IsKeyDown('J') )
        rot.y += deltaTime * speed;
    if( pFramework->IsKeyDown('L') )
        rot.y -= deltaTime * speed;

    if( pFramework->IsKeyDown('I') )
        rot.x -= deltaTime * speed;
    if( pFramework->IsKeyDown('K') )
        rot.x += deltaTime * speed;

    m_ViewMatrix.SetIdentity();
    m_ViewMatrix.Translate( vec3(0,0,-distance) );
    m_ViewMatrix.Rotate( rot.x, 1, 0, 0 );
    m_ViewMatrix.Rotate( rot.y, 0, 1, 0 );
    m_ViewMatrix.Translate( m_LookAtPosition );
    m_ViewMatrix.Inverse();

    GetTransform()->SetRotation( rot );
}

} // namespace fw
