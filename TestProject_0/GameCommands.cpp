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

void Command_MoveLeftUp::Execute()
{
	m_pGameObject->GetSubject()->Notify(m_pGameObject, Event::MoveLeftUp);
}

void Command_MoveLeftDown::Execute()
{
	m_pGameObject->GetSubject()->Notify(m_pGameObject, Event::MoveLeftDown);
}

void Command_MoveRightUp::Execute()
{
	m_pGameObject->GetSubject()->Notify(m_pGameObject, Event::MoveRightUp);
}

void Command_MoveRightDown::Execute()
{
	m_pGameObject->GetSubject()->Notify(m_pGameObject, Event::MoveRightDown);
}
