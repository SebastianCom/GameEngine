#include "Framework.h"

#include "GameObject.h"

namespace fw {

GameObject::GameObject(GameCore* pGame, Mesh* pMesh, ShaderProgram* pShader, Texture* pTexture, vec2 pos)
    : m_pMesh( pMesh )
    , m_pShader( pShader )
    , m_pTexture( pTexture )
    , m_Position( pos )
{
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
    if (m_pPhysicsBody)
    {
        b2Vec2 physicsPosition = m_pPhysicsBody->GetPosition();
        ImGui::Text("%0.2f, %0.2f", physicsPosition.x, physicsPosition.y);
        m_Position.Set(physicsPosition.x, physicsPosition.y);
    }
}

void GameObject::Draw(Camera* pCamera)
{
    vec2 m_Scale = vec2( 1, 1 );

    m_pMesh->Draw( pCamera, m_pShader, m_pTexture, m_Scale, m_Position, m_UVScale, m_UVOffset, 0.0f );
}

void GameObject::CreateBody(PhysicsWorld* pWorld, bool isDynamic, vec2 size, float density)
{
    m_pPhysicsBody = pWorld->CreateBody(isDynamic, size, density);
    m_pPhysicsBody->SetPosition(vec2(7, 9));
    int bp = 1;


    // b2World* pWorld2D = static_cast<PhysicsWorldBox2D*>(pWorld)->Getb2World();

    // b2BodyDef bodyDef;

    //bodyDef.position.Set(m_Position.x, m_Position.y);
    //if (isDynamic)
    //    bodyDef.type = b2_dynamicBody;
    //bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    //b2PolygonShape shape;
    //shape.SetAsBox(size.x / 2, size.y / 2);

    //b2FixtureDef fixtureDef;
    //fixtureDef.shape = &shape;
    //fixtureDef.density = density;

    //m_pPhysicsBody = pWorld2D->CreateBody(&bodyDef);
    //m_pPhysicsBody->CreateFixture(&fixtureDef);
    //int bp = 1;
}

} // namespace fw
