#pragma once
#include <map>
#include <SDL_events.h>
#include <XInput.h>

#include "Commands.h"
#include "Singleton.h"

//TODO improve input manager
namespace dae
{
	enum class ControllerButtons
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		ButtonUp = XINPUT_GAMEPAD_DPAD_UP,
		ButtonDown = XINPUT_GAMEPAD_DPAD_DOWN,
		ButtonRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		ButtonLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		ButtonStart = XINPUT_GAMEPAD_START,
		ButtonBack = XINPUT_GAMEPAD_BACK,
		LeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
		RightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
		LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER
	};

	enum class KeyboardButtons
	{
		Quit = SDLK_ESCAPE
	};

	using ControllerKey = std::pair<unsigned, ControllerButtons>;
	using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Commands>>;
	using KeyboardKey = std::pair<unsigned, KeyboardButtons>;
	using KeyboardCommandsMap = std::map < KeyboardKey, std::unique_ptr<Commands>>;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		void ProcessInput();
		[[nodiscard]] bool IsButtonPressed(ControllerButtons button) const;
		[[nodiscard]] bool IsButtonPressed(KeyboardButtons button) const;
		
		template <typename T>
		void AssignKey(ControllerButtons button, std::unique_ptr<T> command)
		{
			ControllerKey key = std::make_pair(unsigned(button), button);
			m_ConsoleCommands.insert(std::make_pair(key, std::move(command)));
		}

		template <typename T>
		void AssignKey(KeyboardButtons button, std::unique_ptr<T> command)
		{
			KeyboardKey key{ std::make_pair(unsigned(button), button) };
			m_KeyboardCommands.insert(std::make_pair(key, std::move(command)));
		}

		template <typename T>
		void AssignKey(ControllerButtons button)
		{
			ControllerKey key = std::make_pair(unsigned(button), button);
			m_ConsoleCommands.insert(std::make_pair(key, std::make_unique<T>()));
		}

		template <typename T>
		void AssignKey(KeyboardButtons button)
		{
			KeyboardKey key{ std::make_pair(unsigned(button), button) };
			m_KeyboardCommands.insert(std::make_pair(key, std::unique_ptr<T>()));
		}


		
	private:
		void ProcessControllerInput();
		void ProcessKeyboardInput();
		XINPUT_STATE m_CurrentState{};
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

		const std::vector<KeyboardButtons> m_KeyboardButtons
		{
			KeyboardButtons::Quit
		};
	};
}
