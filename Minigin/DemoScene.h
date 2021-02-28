#pragma once
#include "Scene.h"
namespace dae
{
	class DemoScene final :public Scene
	{
	public:
		DemoScene(const std::string& name) : Scene(name)
		{
			InitializeScene();
		};
		~DemoScene() = default;
		DemoScene(const DemoScene& other) = delete;
		DemoScene(DemoScene&& other) = delete;
		DemoScene& operator=(const DemoScene& other) = delete;
		DemoScene& operator=(DemoScene&& other) = delete;

		void InitializeScene() override;
		void UpdateScene() override;
	private:
		void AddPlayers();
		void AddUi(const std::string& font);
		void UpdatePlayer1Lives();
		void UpdatePlayer2Lives();
	};
}
