#pragma once

#include "Math/Vector.h"

namespace fw {

	class PhysicsBody
	{
	public:

		virtual ~PhysicsBody() = 0 {};
		
		virtual void SetPosition(vec3 pos) = 0 {};
		virtual b2Vec2 GetPosition() = 0 {};


	protected:
		vec3 m_Position{ vec3(0,0) };
	};

}