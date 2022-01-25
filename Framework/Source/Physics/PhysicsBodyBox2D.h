#pragma once

#include "Physics/PhysicsBody.h"





namespace fw{

	class PhysicsWorldBox2D;
	
	class PhysicsBodyBox2D : public PhysicsBody
	{
	public:
		
		PhysicsBodyBox2D(PhysicsWorldBox2D* pWorld, bool isDynamic, vec2 size, float density);
		virtual ~PhysicsBodyBox2D();
		virtual void SetPosition(vec2 pos) override;
		virtual  b2Vec2 GetPosition() override;
		b2Body* m_pBody = nullptr;

		b2Body* GetBody();
	protected:
		
	};

}
