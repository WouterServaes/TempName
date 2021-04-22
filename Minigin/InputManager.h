#pragma once
#include <map>
#include <XInput.h>
#include "Singleton.h"
#include <SDL.h>
namespace dae
{
	class Commands;

	enum class ControllerButtons
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
		ButtonUp = 0x0001,
		ButtonDown = 0x0002,
		ButtonRight = 0x0008,
		ButtonLeft = 0x0004,
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
		bool wasDown{ false };

		bool operator<(const KeyboardKey&) const
		{
			return false;
		}
	};

	using ControllerKey = std::pair<unsigned, ControllerButtons>;
	using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Commands>>;

	using KeyboardCommandsMap = std::map<KeyboardKey, std::unique_ptr<Commands>>;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		void SetQuitGamePtr(bool* pQuitGame) { m_pQuitGame = pQuitGame; };
		void ProcessInput();

		[[nodiscard]] bool IsButtonPressed(ControllerButtons button) const;

		template <typename T>
		/// <summary>
		/// Assigns button to command
		/// </summary>
		void AssignKey(ControllerButtons button, std::unique_ptr<T> command)
		{
			ControllerKey key = std::make_pair(unsigned(button), button);
			m_ConsoleCommands.insert(std::make_pair(key, std::move(command)));
		}

		template <typename T>
		/// <summary>
		/// Assigns button to command
		/// </summary>
		void AssignKey(const KeyboardKey& key, std::unique_ptr<T> command)
		{
			m_KeyboardCommands.insert(std::make_pair(key, std::move(command)));
		}

		template <typename T>
		/// <summary>
		/// Assigns button to T, makes a new T
		/// </summary>
		void AssignKey(ControllerButtons button)
		{
			ControllerKey key = std::make_pair(unsigned(button), button);
			m_ConsoleCommands.insert(std::make_pair(key, std::make_unique<T>()));
		}

		template <typename T>
		/// <summary>
		/// Assigns button to T, makes a new T
		/// </summary>
		void AssignKey(const KeyboardKey& key)
		{
			m_KeyboardCommands.insert(std::make_pair(key, std::make_unique<T>()));
		}

	private:
		void ProcessControllerInput();
		void ProcessKeyboardInput();
		void ProcessKeyboardKey(SDL_Keycode sdlKeycode, TriggerState triggerState);
		XINPUT_STATE m_CurrentConsoleState{};

		ControllerCommandsMap m_ConsoleCommands{};
		KeyboardCommandsMap m_KeyboardCommands{};

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

		bool* m_pQuitGame{ nullptr };
	};
}
