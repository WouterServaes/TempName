#pragma once
#include <map>
#include <XInput.h>
#include "Singleton.h"

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

	enum class KeyboardButtons
	{
		Quit = 27, //(SDL_QUIT keysym)
		Space = 32 //(SDL_SCANCODE_SPACE keysym)
	};

	using ControllerKey = std::pair<unsigned, ControllerButtons>;
	using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Commands>>;

	using KeyboardKey = std::pair<unsigned, KeyboardButtons>;
	using KeyboardCommandsMap = std::map < KeyboardKey, std::unique_ptr<Commands>>;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		void SetQuitGamePtr(bool* pQuitGame) { m_pQuitGame = pQuitGame; };
		void ProcessInput();
		[[nodiscard]] bool IsButtonPressed(ControllerButtons button) const;
		[[nodiscard]] bool IsButtonPressed(KeyboardButtons button, int SdlKeyCode) const;

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

		const std::vector<KeyboardButtons> m_KeyboardButtons
		{
			KeyboardButtons::Quit,
			KeyboardButtons::Space
		};
		bool* m_pQuitGame{nullptr};
	};
}
