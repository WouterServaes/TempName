#include "MiniginPCH.h"
#include "MoveCommands.h"

#include "Events.h"
#include "GameObject.h"
#include "Subject.h"

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