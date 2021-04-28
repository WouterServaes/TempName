#include "MiniginPCH.h"

#include "Minigin.h"
#include <chrono>
#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <thread>

#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

#include "Renderer.h"

#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"

#include "Time.h"

#include "AudioServiceLocator.h"
#include "GameAudio.h"
#include "AudioLogger.h"

using namespace std;
using namespace std::chrono;

void Minigin::Run()
{
	Initialize();
	ResourceManager::GetInstance().Init("../Data/");
	LoadGame();

	AudioServiceLocator::ProvideAudioService(new AudioLogger(new GameAudio()));
	AudioServiceLocator::GetAudio()->Start();

	Logger::LogInfo("Running game...");

	{
		auto& renderer{ Renderer::GetInstance() };
		auto& sceneManager{ SceneManager::GetInstance() };
		auto& input{ InputManager::GetInstance() };
		input.SetQuitGamePtr(m_QuitGame);
		auto& time{ Time::GetInstance() };

		auto lastTime{ high_resolution_clock::now() };
		while (!*m_QuitGame)
		{
			const auto currentTime{ high_resolution_clock::now() };
			const float deltaTime{ duration<float>(currentTime - lastTime).count() };

			ImGui_ImplOpenGL2_NewFrame();
			ImGui_ImplSDL2_NewFrame(m_Window);
			ImGui::NewFrame();

			lastTime = currentTime;
			input.ProcessInput();
			time.Update(deltaTime);
			sceneManager.Update();
			renderer.Render();
		}
	}
	Logger::LogInfo("Quit game");
	Cleanup();
}

void Minigin::Initialize()
{
	Logger::LogInfo("Initializing...");
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
	AudioServiceLocator::Initialize();
}

void Minigin::Cleanup()
{
	Logger::LogInfo("Cleaning up...");

	Renderer::GetInstance().Destroy();
	AudioServiceLocator::RemoveService();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
	delete m_QuitGame;
}