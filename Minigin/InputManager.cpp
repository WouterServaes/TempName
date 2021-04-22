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
		const auto dwResult{ UpdateControllerState(i) };
		if (dwResult != ERROR_SUCCESS)
			continue;

		for (auto b : m_ConsoleButtons)
			ProcessControllerButtons(b);
	}
}

DWORD dae::InputManager::UpdateControllerState(int controllerIdx)
{
	ZeroMemory(&m_CurrentConsoleState, sizeof(XINPUT_STATE));
	return XInputGetState(controllerIdx, &m_CurrentConsoleState);
}

void dae::InputManager::ProcessControllerButtons(ControllerButtons button)
{
	for (auto& inputCommandsMap : m_InputCommandsMap)
	{
		if (static_cast<int>(inputCommandsMap.first.ControllerButton) == static_cast<int>(button))
		{
			ProcessControllerCommand(inputCommandsMap.second, IsButtonPressed(button));

			break;
		}
	}
}

void dae::InputManager::ProcessControllerCommand(const std::unique_ptr<Commands>& command, bool buttonPressed)
{
	if (!command->IsActivated())
	{
		if (buttonPressed)
		{
			command->Execute();
			command->SetActivated(true);
		}
	}
	else
	{
		if (!buttonPressed)
			command->SetActivated(false);
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
		default:
			break;
		}
	}
}

void dae::InputManager::ProcessKeyboardKey(SDL_Keycode sdlKeycode, TriggerState triggerState)
{
	for (auto& keyboardCommand : m_InputCommandsMap)
	{
		if (keyboardCommand.first.KeyboardKey.sdlKeyCode == sdlKeycode && keyboardCommand.first.KeyboardKey.triggerState == triggerState)
		{
			keyboardCommand.second->Execute();
			keyboardCommand.second->SetActivated(true);
			break;
		}
	}
}