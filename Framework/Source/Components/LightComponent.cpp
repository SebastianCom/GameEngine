#include "CoreHeaders.h"
#include "LightComponent.h"
#include "Objects/Mesh.h"
#include "Framework.h"



namespace fw {

	LightComponent::LightComponent(vec3 pos, vec3 color, float radius, Mesh* mesh)
		: Component(),
		m_Position(pos),
		m_Color(color),
		m_Radius(radius),
		m_pMesh(mesh)
	{

	}
	LightComponent::~LightComponent()
	{

	}
	void LightComponent::Editor_FillInspectorWindow(int index)
	{	
		ImGui::Text("Light: %i", index+1);

		ImGui::DragFloat3("LightPos", &m_Position.x, 0.01f);
		ImGui::DragFloat3("LightColor", &m_Color.x, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat("LightRadius", &m_Radius, 0.01f);

	}
} // namespace fw
