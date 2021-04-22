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
		switch (e.type)
		{
		case SDL_QUIT:
			*m_pQuitGame = true;
			break;
		case SDL_KEYDOWN:
			ProcessKeyboardKey(e.key.keysym.sym, TriggerState::Down);
			break;
		case SDL_KEYUP:
			ProcessKeyboardKey(e.key.keysym.sym, TriggerState::Released);
			break;

		/*case SDL_MOUSEMOTION:

			break;

		case SDL_MOUSEBUTTONUP:

			break;*/
		default:
			break;
		}
	}
}

void dae::InputManager::ProcessKeyboardKey(SDL_Keycode sdlKeycode, TriggerState triggerState)
{
	for (auto& keyboardCommand : m_KeyboardCommands)
	{
		if (keyboardCommand.first.sdlKeyCode == sdlKeycode && keyboardCommand.first.triggerState == triggerState)
		{
			keyboardCommand.second->Execute();
			keyboardCommand.second->SetActivated(true);
		}
	}
}