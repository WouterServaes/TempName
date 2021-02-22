#include "MiniginPCH.h"
#include "UIComponent.h"
#include "imgui.h"
#include "time.h"
void dae::StartUI::Update()
{
	if (!m_IsInitialized)
	{
		m_IsInitialized = true;
		m_pTransformComponent = m_pGameObject->GetComponent<TransformComponent>();

	}
	const auto transformPos{ m_pTransformComponent->GetPosition() };
	const auto pos = ImVec2(transformPos.x, transformPos.y);
	
	bool activeWindow{ true };
	ImGui::SetNextWindowPos(pos);
	ImGui::Begin("Start UI", &activeWindow, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	ImGui::Button("single player");
	ImGui::Button("co-op");
	ImGui::Button("versus");
	ImGui::End();
}


void dae::FpsUI::Update()
{
	if(!m_IsInitialized)
	{
		m_IsInitialized = true;
		m_pTransformComponent = m_pGameObject->GetComponent<TransformComponent>();
	}
	
	const auto transformPos{ m_pTransformComponent->GetPosition() };
	const auto pos = ImVec2(transformPos.x, transformPos.y);
	const auto size = ImVec2(100, 20);
	bool activeWindow{ true };

	ImGui::SetNextWindowPos(pos);
	ImGui::SetNextWindowSize(size);
	ImGui::Begin("FPS UI", &activeWindow, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove| ImGuiWindowFlags_NoResize);
	ImGui::Text("FPS %i", Time::GetInstance().fps);
	ImGui::End();
}