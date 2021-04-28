#include "MiniginPCH.h"
#include "InputManager.h"

void InputManager::ProcessInput()
{
	ProcessControllerInput();
	ProcessKeyboardInput();
}

bool InputManager::IsButtonPressed(ControllerButtons button, int controllerIdx) const
{
	return (m_CurrentConsoleState[controllerIdx].Gamepad.wButtons & int(button));
}

void InputManager::ProcessControllerInput()
{
	for (int controllerIdx{}; controllerIdx < m_MaxControllerAmount; controllerIdx++)
	{
		const auto dwResult{ UpdateControllerState(controllerIdx) };
		if (dwResult != ERROR_SUCCESS)
			continue;

		for (auto b : m_ConsoleButtons)
			ProcessControllerButtons(b, controllerIdx);
	}
}

DWORD InputManager::UpdateControllerState(int controllerIdx)
{
	ZeroMemory(&m_CurrentConsoleState, sizeof(XINPUT_STATE));
	return XInputGetState(controllerIdx, &m_CurrentConsoleState[controllerIdx]);
}

void InputManager::ProcessControllerButtons(ControllerButtons button, int controllerIdx)
{
	for (auto& inputCommandsMap : m_InputCommandsMap)
	{
		if (inputCommandsMap.first.ControllerNr == controllerIdx &&
			static_cast<int>(inputCommandsMap.first.ControllerButton) == static_cast<int>(button))
		{
			ProcessControllerCommand(inputCommandsMap.second, IsButtonPressed(button, controllerIdx));

			break;
		}
	}
}

void InputManager::ProcessControllerCommand(const std::unique_ptr<Commands>& command, bool buttonPressed)
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

void InputManager::ProcessKeyboardInput()
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

void InputManager::ProcessKeyboardKey(SDL_Keycode sdlKeycode, TriggerState triggerState)
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