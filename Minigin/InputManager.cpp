#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

void dae::InputManager::ProcessInput()
{
	ProcessControllerInput();
	ProcessKeyboardInput();
}

bool dae::InputManager::IsButtonPressed(ControllerButtons button) const
{
	if (m_CurrentState.Gamepad.wButtons & int(button))
		return true;
	return false;
}

bool dae::InputManager::IsButtonPressed(KeyboardButtons button) const
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		
		if (e.type == SDL_KEYUP )
		{
			if(e.key.keysym.sym == int(button))
				return true;
		}
	}
	return false;
}

void dae::InputManager::ProcessControllerInput()
{
	const int connectedControllers{ 1 };
	for (DWORD i = 0; i < connectedControllers; i++)
	{
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		const auto dwResult = XInputGetState(i, &m_CurrentState);
		if (dwResult != ERROR_SUCCESS)
			continue;
		
		for (auto b : m_ConsoleButtons)
		{
			ControllerKey key{ std::make_pair(int(b), b) };
			if (m_ConsoleCommands.find(key) == m_ConsoleCommands.end())
				continue;
			const auto& command{ m_ConsoleCommands.at(key) };
			if (!command->IsActivated())
			{
				if (IsButtonPressed(b))
				{
					command->Execute();
					command->SetActivated(true);
				}
			}
			else
			{
				if (!IsButtonPressed(b))
					command->SetActivated(false);
			}
		}
	}
}

void dae::InputManager::ProcessKeyboardInput()
{
	for (auto b : m_KeyboardButtons)
	{
		KeyboardKey key{ std::make_pair(int(b), b) };
		if (m_KeyboardCommands.find(key) == m_KeyboardCommands.end())
			continue;

		const auto& command{ m_KeyboardCommands.at(key) };
		if (!command->IsActivated())
		{
			if (IsButtonPressed(b))
			{
				command->Execute();
				command->SetActivated(true);
			}
		}
		else
		{
			if (!IsButtonPressed(b))
			{
				command->SetActivated(false);
			}
		}
	}
}