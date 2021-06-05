#pragma once
#include <map>
#include <XInput.h>
#include <SDL.h>
#include "Singleton.h"
#include "Commands.h"
#include "Logger.h"

enum class ControllerButtons
{
	ButtonA = 0x1000,
	ButtonB = 0x2000,
	ButtonX = 0x4000,
	ButtonY = 0x8000,
	ButtonUp = 0x0001,
	ButtonDown = 0x0002,
	ButtonLeft = 0x0004,
	ButtonRight = 0x0008,
	ButtonStart = 0x0010,
	ButtonBack = 0x0020,
	LeftThumb = 0x0040,
	RightThumb = 0x0080,
	LeftShoulder = 0x0100,
	RightShoulder = 0x0200
};

enum class TriggerState
{
	Down, Released
};

struct KeyboardKey
{
	KeyboardKey(SDL_Keycode sdlKeyCode, TriggerState triggerState) :sdlKeyCode(sdlKeyCode), triggerState(triggerState) {};
	SDL_Keycode sdlKeyCode{};
	TriggerState triggerState{ TriggerState::Released };
};

struct InputAction
{
	InputAction(SDL_Keycode sdlKeyCode, TriggerState triggerState, ControllerButtons controllerButton, int controllerNr = 0) :KeyboardKey(sdlKeyCode, triggerState), ControllerButton(controllerButton), ControllerNr(controllerNr) {};
	KeyboardKey KeyboardKey;
	ControllerButtons ControllerButton;
	int ControllerNr;
	//this does not have any use other than making std::map happy
	bool operator<(const InputAction& other) const
	{
		return KeyboardKey.sdlKeyCode < other.KeyboardKey.sdlKeyCode;
	}
};

using InputCommandsMap = std::map<InputAction, std::unique_ptr<Commands>>;

class InputManager final : public Singleton<InputManager>
{
public:
	~InputManager() = default;
	InputManager(const InputManager& other) = delete;
	InputManager(InputManager&& other) noexcept = delete;
	InputManager& operator=(const InputManager& other) = delete;
	InputManager& operator=(InputManager&& other) noexcept = delete;

	void ProcessInput();
	void SetMaxControllerAmount(const int amount)
	{
		if (amount < XUSER_MAX_COUNT) m_MaxControllerAmount = amount;
		else Logger::LogError("InputManager::SetMaxControllerAmount(amount) => amount exceeds allowed amount of 4 ");
	}

	[[nodiscard]] bool IsButtonPressed(ControllerButtons button, int controllerIdx) const;

	template <typename T>
	void AssignKey(const InputAction& inputAction, std::unique_ptr<T> command)
	{
		m_InputCommandsMap.insert(std::make_pair(inputAction, std::move(command)));
	}
private:
	friend class Singleton<InputManager>;
	InputManager() = default;

	void ProcessControllerInput();
	void ProcessKeyboardInput();
	void ProcessKeyboardKey(SDL_Keycode sdlKeycode, TriggerState triggerState);
	DWORD UpdateControllerState(int controllerIdx);
	void ProcessControllerButtons(ControllerButtons button, int controllerIdx);
	void ProcessControllerCommand(const std::unique_ptr<Commands>& command, bool buttonPressed);

	XINPUT_STATE m_CurrentConsoleState[2]{};

	InputCommandsMap m_InputCommandsMap{};

	const std::vector<ControllerButtons> m_ConsoleButtons
	{
		ControllerButtons::ButtonA,
		ControllerButtons::ButtonB,
		ControllerButtons::ButtonX,
		ControllerButtons::ButtonY,
		ControllerButtons::ButtonUp,
		ControllerButtons::ButtonRight,
		ControllerButtons::ButtonDown,
		ControllerButtons::ButtonLeft,
		ControllerButtons::ButtonStart,
		ControllerButtons::ButtonBack,
		ControllerButtons::LeftThumb,
		ControllerButtons::RightThumb,
		ControllerButtons::LeftShoulder,
		ControllerButtons::RightShoulder
	};;

	int m_MaxControllerAmount{ XUSER_MAX_COUNT };
};
