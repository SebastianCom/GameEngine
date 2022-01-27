#pragma once

#include "Physics/PhysicsBody.h"






namespace fw{

	class PhysicsWorld;
	
	class PhysicsBodyBox2D : public PhysicsBody
	{
	public:
		
		PhysicsBodyBox2D(PhysicsWorld* pWorld, bool isDynamic, vec2 size, float density);
		virtual ~PhysicsBodyBox2D() override;
		virtual void SetPosition(vec2 pos) override;
		virtual  b2Vec2 GetPosition() override;
		b2Body* m_pBody = nullptr;

		b2Body* GetBody();
	protected:
		
	};

}
