#include "MiniginPCH.h"
#include "CoilyCreature_Comp.h"

#include "Animation_Comp.h"
#include "CharacterController_Comp.h"
#include "DiskManager_Comp.h"
#include "Events.h"
#include "Scene.h"
#include "Subject.h"
#include "WorldTileManager_Comp.h"
#include "WorldTile_Comp.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/gtx/norm.hpp>

#include "AudioServiceLocator.h"
#pragma warning(pop)

CoilyCreature_Comp::CoilyCreature_Comp(const float timeBetweenJumps, const std::string& coilyAnimationSheet, const int coilyImageAmount, const int coilyFramesPerSecond, const glm::vec2 coilyFrameDimensions) :
	m_TimeBetweenJumps(timeBetweenJumps), m_CoilyImageAmount(coilyImageAmount), m_CoilyFPS(coilyFramesPerSecond), m_CoilyAnimSheet(coilyAnimationSheet), m_CoilyFrameDim(coilyFrameDimensions)
{
}

void CoilyCreature_Comp::Spawn()
{
	m_pAnimationComp = GetComponent<Animation_Comp>();
	m_pDiskManager = m_pGameObject->GetGameObject("DiskManager")->GetComponent<DiskManager_Comp>();
	m_pPlayersTransform.clear();
	for (auto pl : m_pPlayers)
		m_pPlayersTransform.push_back(pl->GetTransform());
	
	m_EggAnimSheet = m_pAnimationComp->GetTextureName();
	m_EggImageAmount = m_pAnimationComp->GetAmountOfFrames();
	m_EggFPS = m_pAnimationComp->GetFramesPerSecond();
	m_EggFrameDim = m_pAnimationComp->GetFrameDimensions();
	m_OriginalScale = m_pTransform->GetUniformScale();
	ChangeToEgg();
	Respawn();
}

void CoilyCreature_Comp::ResetCreature()
{
	m_pGameObject->SetActive(true);
	m_GoToDisk = false;
	ChangeToEgg();
}

void CoilyCreature_Comp::FellOffGrid()
{
	const int tileNr{ m_pCharacterController->GetStandingTileIdx() };
	if (m_pDiskManager->IsDiskNextToTile(tileNr))
	{
		m_pPlayers.at(m_DefeatedByPlayerIndex)->GetSubject()->Notify(m_pPlayers.at(m_DefeatedByPlayerIndex).get(), Event::DefeatedCoily);
		m_pCharacterController->GoToSpawnPos();
		m_GoToDisk = false;
		m_DiskPos = glm::vec2(0.f, 0.f);
		m_pDiskManager->RemoveDisk(tileNr);
		AudioServiceLocator::GetAudio()->PlaySound(2, 100); 
		m_pGameObject->SetActive(false);
	}
	else
		Logger::LogInfo("fell off grid");
}

void CoilyCreature_Comp::PlayerJumpedOnDisk(const glm::vec2 diskPosition)
{
	glm::vec2 pos = m_pTransform->GetPosition();
	const auto distanceToDisk{ glm::distance(pos, diskPosition) };
	if (distanceToDisk <= m_pWorldTileManager->GetGridTileDimensions().x * 2.f)
	{
		m_GoToDisk = true;
		m_DiskPos = diskPosition;
	}
}

void CoilyCreature_Comp::UpdateCreature()
{
	if (m_pCharacterController->CanMove())
	{
		m_ElapsedTime += Time::GetInstance().deltaTime;
		if (m_ElapsedTime >= m_TimeBetweenJumps)
		{
			m_ElapsedTime = 0.f;
			if (m_IsEgg)
				UpdateEgg();
			else
				FollowPlayer();
		}
	}
}

void CoilyCreature_Comp::CollidedWithPlayer(const int playerIndex)
{
	if (!m_IsEgg) m_pPlayers.at(playerIndex)->GetSubject()->Notify(m_pPlayers.at(playerIndex).get(), Event::AttackedByPurple);
}

void CoilyCreature_Comp::UpdateEgg()
{
	const int tileIdx{ m_pWorldTileManager->GetTileIdxAtPosition(m_pTransform->GetPosition()) };

	if (tileIdx >= 0 && tileIdx <= m_pWorldTileManager->GetBottomRowAmount())
		ChangeToSnake();
	else
		BounceToBottom();
}

void CoilyCreature_Comp::BounceToBottom()
{
	const Transform::Side side = (m_LastSide == Transform::Side::Left) ? Transform::Side::Right : Transform::Side::Left;
	if (side == Transform::Side::Left)
		m_pCharacterController->MoveLeftDownOnGrid();
	else
		m_pCharacterController->MoveRightDownOnGrid();
	m_LastSide = side;
}

void CoilyCreature_Comp::ChangeToSnake()
{
	m_IsEgg = false;
	const float rescale{ .35f };
	m_ElapsedTime = 0.f;

	//update texture
	m_pTransform->ScaleUniform(rescale);
	m_pAnimationComp->UpdateAnimationSheet(m_CoilyAnimSheet, m_CoilyImageAmount, m_CoilyFPS, m_CoilyFrameDim);

	//change spawn position because different texture size
	auto spawnPos{ m_pWorldTileManager->GetTileStandPos(m_pWorldTileManager->GetTileAmount()) };

	const auto currentFrameWidth{ m_CoilyFrameDim.x * rescale };
	spawnPos.x -= currentFrameWidth / 2.f;
	m_pCharacterController->SetSpawnPos(spawnPos);

	//change current position because different texture size
	auto currentPos{ m_pWorldTileManager->GetTileAtPosition(m_pTransform->GetPosition())->GetStandPos() };
	currentPos.x -= currentFrameWidth / 2.f;
	m_pTransform->SetPosition(currentPos.x, currentPos.y);
}

void CoilyCreature_Comp::ChangeToEgg()
{
	m_IsEgg = true;
	m_ElapsedTime = 0.f;
	const float rescale{ .1f };
	m_pTransform->ScaleUniform(rescale);

	if (m_pAnimationComp->GetTextureName() != m_EggAnimSheet)
		m_pAnimationComp->UpdateAnimationSheet(m_EggAnimSheet, m_EggImageAmount, m_EggFPS, m_EggFrameDim);

	auto spawnPos{ m_pWorldTileManager->GetTileStandPos(m_pWorldTileManager->GetTileAmount()) };
	const auto frameWidth{ GetConstComponent<Animation_Comp>()->GetFrameDimensions().x * rescale };
	spawnPos.x -= frameWidth / 2.f;
	m_pCharacterController->SetSpawnPos(spawnPos);
}

void CoilyCreature_Comp::FollowPlayer()
{
	const auto& coilyPos{ m_pTransform->GetPosition() };
	glm::vec2 goToPos;
	if (m_GoToDisk)
		goToPos = m_DiskPos;
	else
	{
		float smallestDist{FLT_MAX};
		glm::vec3 closestPos{};

		for(int idx{};idx<m_pPlayersTransform.size();idx++)
		{
			const auto playerPos{ m_pPlayersTransform.at(idx)->GetPosition() };
			const float dist{ glm::distance2(coilyPos, playerPos) };
			if (dist < smallestDist)
			{
				closestPos = playerPos;
				smallestDist = dist;
				m_DefeatedByPlayerIndex = idx;
			}
		}
		goToPos = closestPos;
	}

	

	bool moveLeft{ true };

	//decide direction
	if (goToPos.x > coilyPos.x) //move right
		moveLeft = false;
	else if (goToPos.x == coilyPos.x)//move left or right
		moveLeft = rand() % 10 < 5;

	bool moveUp{ true };
	if (goToPos.y > coilyPos.y) //move down
		moveUp = false;
	else if (goToPos.y == coilyPos.y)//move up or down
		moveUp = rand() % 10 < 5;

	//move in said direction
	if (moveLeft)
	{
		if (moveUp)
			m_pCharacterController->MoveLeftUpOnGrid();
		else
			m_pCharacterController->MoveLeftDownOnGrid();
	}
	else
	{
		if (moveUp)
			m_pCharacterController->MoveRightUpOnGrid();
		else
			m_pCharacterController->MoveRightDownOnGrid();
	}
}