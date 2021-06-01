#pragma once
#include "GameObject.h"

class Scene
{
public:
	static int SceneCount;
	void AddGameObject(const std::shared_ptr<GameObject>& object);
	std::shared_ptr<GameObject>& GetGameObject(int idx);
	std::shared_ptr<GameObject>& GetGameObject(const std::string& gameObjectName);
	void Update();
	void Render() const;
	[[nodiscard]] const std::string& Name() const { return m_Name; };
	explicit Scene(const std::string& name);
	virtual ~Scene() = default;

	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

private:
	void StartScene();
	void StartLateObjects();
	std::string m_Name;
	bool m_StartedScene = false;
	virtual void InitializeScene() = 0;
	std::vector<int> m_InitialStartObjIdxs{}; //This prevents crashes when adding a game object to the scene in the Start() of a component
	std::vector<int> m_ObjIdxsNeedStart{};
protected:
	std::vector < std::shared_ptr<GameObject>> m_Objects{};
	const int sceneNr;
};
