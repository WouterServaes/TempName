#include "MiniginPCH.h"
#include "InputManager.h"
#include "Commands.h"
#include <SDL.h>
#include <XInput.h>

void dae::InputManager::ProcessInput()
{
	ProcessControllerInput();
	ProcessKeyboardInput();
}

bool dae::InputManager::IsButtonPressed(ControllerButtons button) const
{
	return (m_CurrentConsoleState.Gamepad.wButtons & int(button));
}

bool dae::InputManager::IsButtonPressed(KeyboardButtons button, int SdlKeyCode) const
{
	return int(button) == SdlKeyCode;
}

void dae::InputManager::ProcessControllerInput()
{
	const int connectedControllers{ 1 };
	for (DWORD i = 0; i < connectedControllers; i++)
	{
		ZeroMemory(&m_CurrentConsoleState, sizeof(XINPUT_STATE));
		const auto dwResult = XInputGetState(i, &m_CurrentConsoleState);
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
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYUP)
		{
			
			for (auto b : m_KeyboardButtons)
			{
				KeyboardKey key{ std::make_pair(int(b), b) };
				if (m_KeyboardCommands.find(key) == m_KeyboardCommands.end())
					continue;

				const auto& command{ m_KeyboardCommands.at(key) };

				const auto sdlKeycode{ e.key.keysym.sym };
				if (!command->IsActivated())
				{
					if (IsButtonPressed(b, sdlKeycode))
					{
						command->Execute();
						command->SetActivated(true);
					}
				}
				else
				{
					if (!IsButtonPressed(b, sdlKeycode))
					{
						command->SetActivated(false);
					}
				}
			}
		}
		else if (e.type == SDL_QUIT )
		{
			*m_pQuitGame = true;
		}
	}
}