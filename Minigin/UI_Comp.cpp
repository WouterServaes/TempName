#include "MiniginPCH.h"
#include "UI_Comp.h"
#include "imgui.h"
#include "Time.h"
#include "GameObject.h"
#include "Transform.h"
#include "Transform_Comp.h"

void UI_Comp::Start()
{
	m_pTransform = m_pGameObject->GetComponent<Transform_Comp>()->GetTransform();
}

void FpsUI::Update()
{
	const auto transformPos{ m_pTransform->GetPosition() };
	const auto pos = ImVec2(transformPos.x, transformPos.y);
	const auto size = ImVec2(100, 20);
	bool activeWindow{ true };

	ImGui::SetNextWindowPos(pos);
	ImGui::SetNextWindowSize(size);
	ImGui::Begin("FPS UI", &activeWindow, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	ImGui::Text("FPS %i", Time::GetInstance().fps);
	ImGui::End();
}