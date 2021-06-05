#pragma once
#include <Scene.h>
class LevelScene final:public Scene
{
public:
	explicit LevelScene(const std::string& name) : Scene(name)
	{
		InitializeScene();
	};
	~LevelScene() = default;
	LevelScene(const LevelScene & other) = delete;
	LevelScene(LevelScene && other) = delete;
	LevelScene& operator=(const LevelScene & other) = delete;
	LevelScene& operator=(LevelScene && other) = delete;

	void InitializeScene() override;
	void Restart() override;
private:
	//ui game object
	void InitUi();

	//world 
	void InitWorld();
	
	//players
	void InitPlayer();

	//Coily
	void InitCoily();

	void InitGreen();

	void InitPurple();

	void InitDisks();

	void InitGameController();


	
};

