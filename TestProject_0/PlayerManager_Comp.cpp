#include "MiniginPCH.h"
#include "PlayerManager_Comp.h"


#include "Animation_Comp.h"
#include "CharacterController_Comp.h"
#include "CharacterObserver.h"
#include "Health_Comp.h"
#include "MovementObserver.h"
#include "Player_Comp.h"
#include "Render_Comp.h"
#include "Scene.h"
#include "ScoreObserver.h"
#include "Score_Comp.h"
#include "Subject.h"
#include "TileChanger_Comp.h"
#include "Transform.h"

void PlayerManager_Comp::AddPlayer()
{
	auto pPlayerObj{ std::make_shared< GameObject>("pl" + std::to_string(m_PlayerCount), true) };
	
	m_pGameObject->GetCurrentScene()->AddGameObject(pPlayerObj);
	pPlayerObj->AddComponent(new Render_Comp());
	const int imgAmount{ 4 };
	const int fps{ 8 };
	auto* pAnimComp{ new Animation_Comp("Images/QBert.png", imgAmount, fps, glm::vec2(128.f, 147.f)) };
	pPlayerObj->AddComponent(pAnimComp);
	pPlayerObj->AddComponent(new CharacterController_Comp(.025f));
	pPlayerObj->AddComponent(new Player_Comp(10));
	pPlayerObj->AddComponent(new TileChanger_Comp());
	auto* pPlScore{ new Score_Comp() };
	pPlayerObj->AddComponent(pPlScore);
	auto* pPlHealth{ new Health_Comp(3, 3) };
	pPlayerObj->AddComponent(pPlHealth);
	pPlayerObj->GetSubject()->AddObserver(new MovementObserver());
	pPlayerObj->GetSubject()->AddObserver(new ScoreObserver());
	pPlayerObj->GetSubject()->AddObserver(new CharacterObserver());
	pPlayerObj->SetRenderLayer(5);
	pPlayerObj->GetTransform()->ScaleUniform(.25f);
	m_pPlayers.push_back(pPlayerObj);
	m_PlayerCount++;
}

const std::vector<std::shared_ptr<GameObject>>& PlayerManager_Comp::GetPlayers() const
{
	return m_pPlayers;
}

void PlayerManager_Comp::ResetPlayers()
{
	for (auto pl : m_pPlayers)
		pl->GetComponent<Player_Comp>()->ResetPlayer();
}
