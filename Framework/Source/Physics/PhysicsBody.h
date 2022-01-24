#pragma once

#include "Math/Vector.h"

namespace fw {

	class PhysicsBody
	{
	public:

		virtual ~PhysicsBody() = 0 {};
		
		virtual void SetPosition(vec2 pos) { m_Position = pos; }
		virtual vec2 GetPosition() { return m_Position; }

	protected:
		vec2 m_Position{ vec2(0,0) };
	};

}