#include "PhysicsWorld.h"

namespace fw {
	
	const vec2 PhysicsWorld::c_DefaultGravity = vec2(0, -9.8f);

	PhysicsBody* PhysicsWorld::CreateBody(bool isDynamic, vec2 size, float density)
	{
		m_pBody = new PhysicsBody(isDynamic, size, density);
		return m_pBody;
	}
}
