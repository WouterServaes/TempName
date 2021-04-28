#include "MiniginPCH.h"
#include "Commands.h"

#include "GameObject.h"

Commands::Commands(GameObject* gameObject)
	:m_pGameObject(gameObject)
{}

bool Commands::IsActivated() const
{
	return m_Activated;
}

void Commands::SetActivated(const bool activated)
{
	m_Activated = activated;
}

Command_QuitGame::Command_QuitGame(bool* quitGame)
	:m_pQuitGame(quitGame)
{}

void Command_QuitGame::Execute()
{
	*m_pQuitGame = true;
}