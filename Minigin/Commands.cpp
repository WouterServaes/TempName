#include "MiniginPCH.h"
#include "Commands.h"

dae::Commands::Commands(std::shared_ptr<GameObject> gameObject)
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
