#pragma once
#include <Scene.h>
class VersusScene final:public Scene
{
public:
	explicit VersusScene(const std::string& name) : Scene(name)
	{
		InitializeScene();
	};
	~VersusScene() = default;
	VersusScene(const VersusScene & other) = delete;
	VersusScene(VersusScene && other) = delete;
	VersusScene& operator=(const VersusScene & other) = delete;
	VersusScene& operator=(VersusScene && other) = delete;

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

