#include "CoreHeaders.h"

#include "PhysicsBodyBullet3D.h"
#include "PhysicsWorldBullet3D.h"
#include "Math/Matrix.h"
#include "Math/Vector.h"

#include "btBulletDynamicsCommon.h"

namespace fw {

PhysicsBodyBullet3D::PhysicsBodyBullet3D(PhysicsWorldBullet3D* pWorld, btRigidBody* pRigidBody)
{
    m_pWorld = pWorld;
    m_pBody = pRigidBody;
}

PhysicsBodyBullet3D::~PhysicsBodyBullet3D()
{
    m_pWorld->m_pWorld->removeRigidBody( m_pBody );
    delete m_pBody->getMotionState();
    delete m_pBody->getCollisionShape();
    delete m_pBody;
}

vec3 PhysicsBodyBullet3D::GetPosition()
{
    btVector3 pos = m_pBody->getWorldTransform().getOrigin();
    return vec3( pos.x(), pos.y(), pos.z() );
}

vec3 PhysicsBodyBullet3D::GetRotation()
{
    // Grab the bullet transform.
    btTransform transform = m_pBody->getWorldTransform();

    // Convert it to a transform matrix.
    mat4 matrix;
    transform.getOpenGLMatrix( &matrix.m11 );

    // Convert it to angles.
    vec3 angles = matrix.GetEulerAngles();
    return angles;
}

void PhysicsBodyBullet3D::SetTransform(vec3 pos, vec3 rot)
{
}

void PhysicsBodyBullet3D::SetEnabled(bool bEnabled)
{
    
}

void PhysicsBodyBullet3D::ApplyForceToCenter(vec3 force)
{
    m_pBody->applyCentralForce( btVector3(force.x, force.y, force.z) );
    m_pBody->activate( true );
}

void PhysicsBodyBullet3D::Editor_FillInspectorWindow()
{
}

} // namespace fw
