#pragma once

#include "Math/Vector.h"

namespace fw {

	class PhysicsBody
	{
	public:

		virtual ~PhysicsBody() = 0 {};
		
		virtual void SetPosition(vec3 pos) = 0 {};
		virtual b2Vec2 GetPosition() = 0 {};
		virtual void SetRotation(vec3 rot) = 0 {};
		virtual vec3 GetRotation() = 0 {};
		virtual b2Body* GetBody() = 0 {};
		virtual vec2 GetSize() = 0 {};


	protected:
		vec3 m_Position{ vec3(0,0) };
		vec3 m_Rotation{ vec3(0,0) };
		vec3 m_Scale{ vec3(0,0) };
	};

}