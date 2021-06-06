#pragma once
#include <Scene.h>
class CoopScene final:public Scene
{
public:
	explicit CoopScene(const std::string& name) : Scene(name)
	{
		InitializeScene();
	};
	~CoopScene() = default;
	CoopScene(const CoopScene & other) = delete;
	CoopScene(CoopScene && other) = delete;
	CoopScene& operator=(const CoopScene & other) = delete;
	CoopScene& operator=(CoopScene && other) = delete;

	void InitializeScene() override;
	void Restart() override;

private:
	void InitUi();

	void InitWorld();

	void InitPlayers();
	
	void InitCoily();

	void InitGreen();

	void InitPurple();

	void InitDisks();

	void InitGameController();
	
};

