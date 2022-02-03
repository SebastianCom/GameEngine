#include "CoreHeaders.h"

#include "Component.h"

namespace fw {
    Component::Component()
    {
    }
    Component::Component(GameObject* pGameObject)
    : m_pGameObject( pGameObject )
{
}

Component::~Component()
{
}

} // namespace fw
