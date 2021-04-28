#include "MiniginPCH.h"
#include "GameCommands.h"

#include "Events.h"
#include "Health_Comp.h"
#include "GameObject.h"
#include "Subject.h"
void Command_RemoveHp::Execute()
{
	m_pGameObject->GetComponent<Health_Comp>()->RemoveHealth(1.f);
}

void Command_ColorChanged::Execute()
{
	m_pGameObject->GetSubject()->Notify(m_pGameObject, Event::ColorChanged);
}

void Command_DefeatedCoily::Execute()
{
	m_pGameObject->GetSubject()->Notify(m_pGameObject, Event::DefeatedCoily);
}

void Command_CatchedSlickOrSam::Execute()
{
	m_pGameObject->GetSubject()->Notify(m_pGameObject, Event::CatchedSlickOrSam);
}

void Command_Move::Execute()
{
	m_pGameObject->GetSubject()->Notify(m_pGameObject, Event::Move);
}
