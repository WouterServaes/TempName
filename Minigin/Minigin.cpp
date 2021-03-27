#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <SDL.h>

#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

#include "Renderer.h"

#include "imgui_impl_opengl2.h"
#include "imgui_impl_sdl.h"


#include "Time.h"
#include "Commands.h"

#include "DemoScene.h"

#include "ServiceLocator.h"
#include "GameAudio.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Run()
{
	Initialize();
	ResourceManager::GetInstance().Init("../Data/");
	LoadGame();
	
	ServiceLocator::ProvideAudioService(new GameAudio());
	ServiceLocator::GetAudio()->Start();
	
	{
		auto& renderer{ Renderer::GetInstance() };
		auto& sceneManager{ SceneManager::GetInstance() };
		auto& input{ InputManager::GetInstance() };
		auto* audio{ ServiceLocator::GetAudio() };
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
			audio->Update();
		}
		
	}
	Cleanup();
}


void dae::Minigin::Initialize()
{
	
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
	ServiceLocator::Initialize();
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& sceneManager{ SceneManager::GetInstance() };
	sceneManager.AddScene(std::make_shared<DemoScene>("Demo"));

	auto& inputManager{ InputManager::GetInstance() };
	inputManager.AssignKey(KeyboardButtons::Quit, std::make_unique<Command_QuitGame>(m_QuitGame));
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	ServiceLocator::RemoveService();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
	delete m_QuitGame;
}
