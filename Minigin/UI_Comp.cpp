#include "MiniginPCH.h"
#include "UI_Comp.h"
#include "imgui.h"
#include "Time.h"
#include "GameObject.h"
#include "Transform.h"
#include "Transform_Comp.h"


void dae::UI_Comp::Start()
{
	m_pTransformComponent = m_pGameObject->GetComponent<Transform_Comp>();

}

void dae::StartUI::Update()
{
	const auto& transformPos{ m_pTransformComponent->GetTransform()->GetPosition() };
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
	const auto transformPos{ m_pTransformComponent->GetTransform()->GetPosition() };
	const auto pos = ImVec2(transformPos.x, transformPos.y);
	const auto size = ImVec2(100, 20);
	bool activeWindow{ true };

	ImGui::SetNextWindowPos(pos);
	ImGui::SetNextWindowSize(size);
	ImGui::Begin("FPS UI", &activeWindow, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	ImGui::Text("FPS %i", Time::GetInstance().fps);
	ImGui::End();
}