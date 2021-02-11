#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"


#include "TextComponent.h"
#include "TransformComponent.h"
#include "FpsComponent.h"

using namespace std;
using namespace std::chrono;

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
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//should be: load file in, create objects using this file
	
	//game objects
	auto go = std::make_shared<GameObject>();
	go->AddComponent(std::make_unique<RenderComponent>("background.jpg"));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_unique<RenderComponent>("logo.png"));
	go->AddComponent(std::make_unique<TransformComponent>(216.f, 180.f));
	scene.Add(go);

	go = make_shared<GameObject>();
	go->AddComponent(std::make_unique<TextComponent>("Programming 4 Assignment", "Lingua.otf", 36));
	go->AddComponent(std::make_unique<TransformComponent>(80.f, 20.f));
	scene.Add(go);

	go = make_shared<GameObject>();
	go->AddComponent(std::make_unique<TextComponent>("00 FPS", "Lingua.otf", 20, glm::vec4{ 0.f, 255.f, 0.f, 1.f }));
	go->AddComponent(std::make_unique<FpsComponent>(true));
	go->AddComponent(std::make_unique<TransformComponent>(5.f, 5.f));
	scene.Add(go);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer{ Renderer::GetInstance() };
		auto& sceneManager {SceneManager::GetInstance()};
		auto& input{ InputManager::GetInstance() };

		bool doContinue{ true };
		auto lastTime{ high_resolution_clock::now() };
		float lag{0.f};
		
		while (doContinue)
		{
			const auto currentTime {high_resolution_clock::now()};
			const float deltaTime{duration<float>(currentTime - lastTime).count()};
			lastTime = currentTime;
			lag += deltaTime;
			
			doContinue = input.ProcessInput();

			auto& time{ Time::GetInstance() };
			time.deltaTime = MsPerUpdate;
			time.SetFps();
			while (lag>= MsPerUpdate)
			{
				sceneManager.Update();
				lag -= MsPerUpdate;
			}
			renderer.Render();
		}
	}
	Cleanup();
}
