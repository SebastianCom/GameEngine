#pragma once

#include "Physics/PhysicsBody.h"

namespace fw{
	class PhysicsBodyBox2D : public PhysicsBody
	{
		PhysicsBodyBox2D(bool isDynamic, vec2 size, float density);
		virtual ~PhysicsBodyBox2D();

	protected:
		b2Body* m_pBody = nullptr;
	};

}
