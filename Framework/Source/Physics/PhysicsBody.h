#pragma once

#include "Math/Vector.h"

namespace fw {

	class PhysicsBody
	{
	public:

		virtual ~PhysicsBody() = 0 {};
		
		virtual void SetPosition(vec2 pos) = 0 {};
		virtual b2Vec2 GetPosition() = 0 {};


	protected:
		vec2 m_Position{ vec2(0,0) };
	};

}