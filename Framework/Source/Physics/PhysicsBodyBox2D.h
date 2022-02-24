#pragma once

#include "Physics/PhysicsBody.h"






namespace fw{

	class PhysicsWorld;
	class GameObject;
	
	class PhysicsBodyBox2D : public PhysicsBody
	{
	public:
		
		PhysicsBodyBox2D(PhysicsWorld* pWorld, bool isDynamic, vec2 size, float density, GameObject* gameOb);
		PhysicsBodyBox2D(PhysicsWorld* pWorld, bool isDynamic, vec2 size, float density, GameObject* gameOb, const char* shape);
		virtual ~PhysicsBodyBox2D() override;
		virtual void SetPosition(vec3 pos) override;
		virtual  b2Vec2 GetPosition() override;
		virtual void SetRotation(vec3 rot) override;
		virtual vec3 GetRotation() override;
		virtual vec2 GetSize() override;
		b2Body* m_pBody = nullptr;

		virtual void Editor_FillInspectorWindow() override;

		virtual b2Body* GetBody() override;
	protected:
		
		vec2 m_Size;
	};

}
