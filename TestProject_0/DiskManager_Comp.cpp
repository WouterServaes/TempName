#include "MiniginPCH.h"
#include "DiskManager_Comp.h"

#include "Animation_Comp.h"
#include "FloatingDisk_Comp.h"
#include "Render_Comp.h"
#include "Scene.h"
#include "WorldTileManager_Comp.h"
DiskManager_Comp::DiskManager_Comp(std::vector<DiskPos>& diskPositions)
	:m_DiskPositions(std::move(diskPositions))
{
}

void DiskManager_Comp::Start()
{
	m_pWorldTileManager = m_pGameObject->GetGameObject("WorldTileManager")->GetComponent<WorldTileManager_Comp>();
	MakeDisks();
}

bool DiskManager_Comp::IsDiskNextToPos(const glm::vec2 position) const
{
	const int tileIdxAtPos{ m_pWorldTileManager->GetTileIdxAtPosition(position) };
	const auto it{ std::find_if(m_pDisks.begin(), m_pDisks.end(), [tileIdxAtPos](const FloatingDisk_Comp* pDisk)
		{
			return pDisk->GetTileIdxNextToDisk() == tileIdxAtPos;
		}) };
	return it != m_pDisks.end();
}

void DiskManager_Comp::MakeDisks()
{
	auto* pScene{ m_pGameObject->GetCurrentScene() };
	for (int idx{}; idx < m_DiskPositions.size(); idx++)
	{
		const auto name{ "Disk" + std::to_string(idx) };
		auto pDisk{ std::make_shared<GameObject>(name) };
		pScene->AddGameObject(pDisk);
		pDisk->AddComponent(new Render_Comp());
		pDisk->AddComponent(new Animation_Comp("Images/FloatingDisk.png", 4, 8, glm::vec2(128, 73)));
		auto* pDiskComp{ new FloatingDisk_Comp(m_DiskPositions.at(idx)) };
		m_pDisks.push_back(pDiskComp);
		pDisk->AddComponent(pDiskComp);
		pDisk->GetTransform()->ScaleUniform(.25f);
	}
}