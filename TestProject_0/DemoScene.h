#pragma once
#include "Scene.h"
#include <string>

class DemoScene final :public Scene
{
public:
	explicit DemoScene(const std::string& name) : Scene(name)
	{
		InitializeScene();
	};
	~DemoScene() = default;
	DemoScene(const DemoScene& other) = delete;
	DemoScene(DemoScene&& other) = delete;
	DemoScene& operator=(const DemoScene& other) = delete;
	DemoScene& operator=(DemoScene&& other) = delete;

	void InitializeScene() override;
private:
	void AddPlayers();
	void AddUi(const std::string& font);
	void InitInput();
};
