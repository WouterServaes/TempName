#pragma once
#include <Scene.h>
class LevelOneScene final:public Scene
{
public:
	explicit LevelOneScene(const std::string& name) : Scene(name)
	{
		InitializeScene();
	};
	~LevelOneScene() = default;
	LevelOneScene(const LevelOneScene & other) = delete;
	LevelOneScene(LevelOneScene && other) = delete;
	LevelOneScene& operator=(const LevelOneScene & other) = delete;
	LevelOneScene& operator=(LevelOneScene && other) = delete;

	void InitializeScene() override;
private:
	//ui game object
	void InitUi();

	//world 
	void InitWorld();
	
	//players
	void InitPlayerManager();

	//Coily
	void InitCoily();
};

