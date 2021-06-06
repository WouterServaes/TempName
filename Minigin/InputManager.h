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
	KeyboardKey(const SDL_Keycode sdlKeyCode,const TriggerState triggerState) :sdlKeyCode(sdlKeyCode), triggerState(triggerState) {};
	SDL_Keycode sdlKeyCode{};
	TriggerState triggerState{ TriggerState::Released };
};

struct InputAction
{
	InputAction(const SDL_Keycode sdlKeyCode, const TriggerState triggerState, const ControllerButtons controllerButton,const int controllerNr = 0)
	:KeyboardKey(sdlKeyCode, triggerState), ControllerButton(controllerButton), ControllerNr(controllerNr) {};
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

	void Start();
	
	/// <summary>
	/// Processes input for controller and keyboard
	/// </summary>
	void ProcessInput();

	/// <summary>
	/// Sets the max controller amount
	/// </summary>
	void SetMaxControllerAmount(const int amount)
	{
		if (amount < XUSER_MAX_COUNT) m_MaxControllerAmount = amount;
		else Logger::LogError("InputManager::SetMaxControllerAmount(amount) => amount exceeds allowed amount of " + std::to_string(XUSER_MAX_COUNT));

		m_CurrentConsoleState.resize(m_MaxControllerAmount);
	}

	///Returns true if a button is pressed on the specified controller
	[[nodiscard]] bool IsButtonPressed(ControllerButtons button, int controllerIdx) const;

	/// <summary>
	/// Assigns an input action to a Command
	/// </summary>
	void AssignKey(const InputAction& inputAction, std::unique_ptr<Commands> command)
	{
		m_InputCommandsMap.insert(std::make_pair(inputAction, std::move(command)));
	}
private:
	friend class Singleton<InputManager>;
	InputManager() = default;

	/// <summary>
	/// Processes controller input, calls UpdateControllerState and ProcessControllerButtons
	/// </summary>
	void ProcessControllerInput();

	/// <summary>
	/// Processes keyboard input, calls ProcessKeyboardKey
	/// </summary>
	void ProcessKeyboardInput();

	/// <summary>
	/// Processes keyboard key
	/// </summary>
	void ProcessKeyboardKey(SDL_Keycode sdlKeycode, TriggerState triggerState);

	/// <summary>
	/// Updates state of a controller using XInputGetState and returns it
	/// </summary>
	DWORD UpdateControllerState(int controllerIdx);

	/// <summary>
	/// Processes controller buttons of controller, calls ProcessControllerCommand
	/// </summary>
	void ProcessControllerButtons(ControllerButtons button, int controllerIdx);

	/// <summary>
	/// Enables, disables and executes a command
	/// </summary>
	void ProcessControllerCommand(const std::unique_ptr<Commands>& command, bool buttonPressed);

	/// <summary>
	/// Holds the states of each controller
	/// </summary>
	std::vector<XINPUT_STATE> m_CurrentConsoleState{};

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
