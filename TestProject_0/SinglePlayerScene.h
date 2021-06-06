#pragma once
#include <Scene.h>
class SinglePlayerScene final:public Scene
{
public:
	explicit SinglePlayerScene(const std::string& name) : Scene(name)
	{
		InitializeScene();
	};
	~SinglePlayerScene() = default;
	SinglePlayerScene(const SinglePlayerScene & other) = delete;
	SinglePlayerScene(SinglePlayerScene && other) = delete;
	SinglePlayerScene& operator=(const SinglePlayerScene & other) = delete;
	SinglePlayerScene& operator=(SinglePlayerScene && other) = delete;

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

