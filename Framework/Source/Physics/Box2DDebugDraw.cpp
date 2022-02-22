#include "Box2DDebugDraw.h"


namespace fw {






	void MyDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
	}

	void MyDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		for (int i = 0; i < vertexCount; i++)
		{
			VertexFormat temp = { vec3(vertices->x, vertices->y, 0), 255,255,255,255,  vec2(0.0f,1.0f) };
			m_Verts.push_back(temp);
		}

	}

	void MyDebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
	{
	}

	void MyDebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
	{
	}

	void MyDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
	}

	void MyDebugDraw::DrawTransform(const b2Transform& xf)
	{
	}

	void MyDebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
	{
	}

}
