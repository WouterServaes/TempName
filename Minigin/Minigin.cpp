#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "FpsCounter.h"

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

	//game components
	auto go = std::make_shared<GameObject>();
	go->AddRenderComponent("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddRenderComponent("logo.png");
	go->SetPosition(216, 180);
	scene.Add(go);

	//text components
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<TextObject>( "Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	to = std::make_shared<TextObject>("00 FPS", font);
	to->SetPosition(5, 5);
	to->AddFpsComponent();
	scene.Add(to);
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
			Time::GetInstance().deltaTime = MsPerUpdate;
			FpsCounter::GetInstance().SetFps();
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
