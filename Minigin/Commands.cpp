#include "MiniginPCH.h"
#include "Commands.h"

#include "Events.h"
#include "GameObject.h"
#include "Health_Comp.h"
#include "Score_Comp.h"
#include "Subject.h"

dae::Commands::Commands(std::shared_ptr<GameObject>& gameObject)
	:m_pGameObject(gameObject)
{}

bool dae::Commands::IsActivated() const
{
	return m_Activated;
}

void dae::Commands::SetActivated(bool activated)
{
	m_Activated = activated;
}

dae::Command_QuitGame::Command_QuitGame(bool* quitGame)
	:m_pQuitGame(quitGame)
{}

void dae::Command_QuitGame::Execute()
{
	*m_pQuitGame = true;
}

void dae::Command_RemoveHp::Execute()
{
	m_pGameObject->GetComponent<Health_Comp>()->RemoveHealth(1.f);
}

void dae::Command_ColorChanged::Execute()
{
	m_pGameObject->GetSubject()->Notify(m_pGameObject, Event::ColorChanged);
}

void dae::Command_DefeatedCoily::Execute()
{
	m_pGameObject->GetSubject()->Notify(m_pGameObject, Event::DefeatedCoily);
}

void dae::Command_CatchedSlickOrSam::Execute()
{
	m_pGameObject->GetSubject()->Notify(m_pGameObject, Event::CatchedSlickOrSam);
}