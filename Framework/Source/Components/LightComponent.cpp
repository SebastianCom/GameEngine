#include "CoreHeaders.h"
#include "LightComponent.h"
#include "Objects/Mesh.h"



namespace fw {

	LightComponent::LightComponent(vec3 pos, vec3 color, float radius, Mesh* mesh)
		: Component(),
		m_Position(pos),
		m_Color(color),
		m_Radius(radius),
		m_pMesh(mesh)
	{
		m_pMesh->AddLightComponent(this);
	}
	LightComponent::~LightComponent()
	{

	}
	void LightComponent::Editor_FillInspectorWindow()
	{
		//TODO
	}
} // namespace fw
