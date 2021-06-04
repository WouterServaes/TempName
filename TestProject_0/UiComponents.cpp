#include "MiniginPCH.h"
#include "UiComponents.h"

#include "imgui.h"
#include "SceneManager.h"
#include "Transform_Comp.h"
#include "Transform.h"
void StartUI::Update()
{
	const auto& transformPos{ m_pTransformComponent->GetTransform()->GetPosition() };
	const auto pos = ImVec2(transformPos.x, transformPos.y);

	bool activeWindow{ true };
	ImGui::SetNextWindowPos(pos);
	ImGui::Begin("Start UI", &activeWindow, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	if(ImGui::Button("single player"))
	{
		SceneManager::GetInstance().LoadScene("Level");
		//get current scene -> get game controller -> set game mode
	}
	
	if(ImGui::Button("co-op"))
	{
		SceneManager::GetInstance().LoadScene("Level");
		//get current scene -> get game controller -> set game mode
	}
	
	if(ImGui::Button("versus"))
	{
		SceneManager::GetInstance().LoadScene("Level");
		//get current scene -> get game controller -> set game mode
	}
	ImGui::End();
}
