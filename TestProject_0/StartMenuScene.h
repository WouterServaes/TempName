#pragma once
#include <Scene.h>
class StartMenuScene final:public Scene
{
public:
	explicit StartMenuScene(const std::string& name) : Scene(name)
	{
		InitializeScene();
	};
	~StartMenuScene() = default;
	StartMenuScene(const StartMenuScene & other) = delete;
	StartMenuScene(StartMenuScene && other) = delete;
	StartMenuScene& operator=(const StartMenuScene & other) = delete;
	StartMenuScene& operator=(StartMenuScene && other) = delete;

	void InitializeScene() override;
private:
};

