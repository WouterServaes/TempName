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
#include "WorldTileManager_Comp.h"

void PlayerManager_Comp::AddPlayer()
{
	auto pPlayerObj{ std::make_shared< GameObject>("Player" + std::to_string(m_PlayerCount), true) };

	m_pGameObject->GetCurrentScene()->AddGameObject(pPlayerObj);
	pPlayerObj->AddComponent(new Render_Comp());
	const int imgAmount{ 4 };
	const int fps{ 8 };
	auto* pAnimComp{ new Animation_Comp("Images/QBert.png", imgAmount, fps, glm::vec2(128.f, 147.f)) };
	pPlayerObj->AddComponent(pAnimComp);
	pPlayerObj->AddComponent(new CharacterController_Comp(.025f));
	pPlayerObj->AddComponent(new Player_Comp(m_PlayerCount));
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

void PlayerManager_Comp::Update()
{
	if (!m_Started)
	{
		m_Started = true;
		SetSpawnPosition();
	}
}

void PlayerManager_Comp::SetSpawnPosition()
{
	const auto pWorldGrid{ m_pGameObject->GetCurrentScene()->GetGameObject("WorldTileManager") };
	const auto pWorldGridManagerComp{ pWorldGrid->GetConstComponent<WorldTileManager_Comp>() };
	std::vector<int> spawnTiles{};

	if (m_PlayerCount > 1)
	{
		spawnTiles.push_back(0);
		spawnTiles.push_back(pWorldGridManagerComp->GetBottomRowAmount());
	}
	else
		spawnTiles.push_back(pWorldGridManagerComp->GetTileAmount());

	glm::vec2 spawnPos{};

	const auto playerTextureWidth{ m_pPlayers.at(0)->GetConstComponent<Animation_Comp>()->GetFrameDimensions().x };

	for (int idx{}; idx < m_PlayerCount; idx++)
	{
		auto pPlayer{ m_pPlayers.at(idx) };
		spawnPos = pWorldGridManagerComp->GetTileStandPos(spawnTiles.at(idx));
		auto* pTransform{ pPlayer->GetTransform() };
		spawnPos.x -= (playerTextureWidth * pTransform->GetUniformScale()) / 2.f;
		pTransform->SetPosition(spawnPos.x, spawnPos.y);
		pPlayer->GetComponent<CharacterController_Comp>()->SetSpawnPos(spawnPos);
	}
}