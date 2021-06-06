#pragma once
#include "GameObject.h"

class InputManager;
class Scene
{
public:
	static int SceneCount;
	
	explicit Scene(const std::string& name);
	virtual ~Scene() = default;

	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

	/// <summary>
	/// Adds a GameObject to the current scene. Start of gameObject's components will be called next Update
	/// </summary>
	void AddGameObject(const std::shared_ptr<GameObject>& object);

	/// <summary>
	/// Returns a GameObject on position "idx" from the GameObjects of this scene
	/// </summary>
	std::shared_ptr<GameObject>& GetGameObject(int idx);

	/// <summary>
	/// Returns a GameObject with given name 
	/// </summary>
	std::shared_ptr<GameObject>& GetGameObject(const std::string& gameObjectName);

	/// <summary>
	/// Calls Update() of every GameObject\n
	/// Calls Start() in the first scene Update\n
	/// Calls StartLateObjects() when an object is added after the scene has started
	/// </summary>
	void Update();

	/// <summary>
	/// Calls Render() of every GameObject
	/// </summary>
	void Render() const;

	///Returns the name of the scene
	[[nodiscard]] const std::string& Name() const { return m_Name; }

	/// <summary>
	/// Restarts the scene. \n
	/// If the scene hasn't started yet, it starts the scene instead
	/// </summary>
	void RestartScene();

	[[nodiscard]] std::shared_ptr<InputManager>& GetInputManager() { return m_pInputManager; }
private:
	/// <summary>
	///  Calls Start() on added GameObjects 
	/// </summary>
	void StartScene();

	/// <summary>
	///  Calls Start() on newly added GameObjects 
	/// </summary>
	void StartLateObjects();
	
	std::string m_Name;
	bool m_StartedScene = false;

	/// <summary>
	/// Initializes the scenes, used to add GameObjects to the scene
	/// </summary>
	virtual void InitializeScene() = 0;

	/// <summary>
	/// Used to restart the scene\n
	/// It made more sense to have a defined Restart function in a project of this scope,
	/// Instead of making and deleting a whole scene
	/// </summary>
	virtual void Restart(){};
	
	std::vector<int> m_InitialStartObjIdxs{}; //This prevents crashes when adding a game object to the scene in the Start() of a component
	std::vector<int> m_ObjIdxsNeedStart{};
	std::shared_ptr<InputManager> m_pInputManager{nullptr};
protected:
	std::vector < std::shared_ptr<GameObject>> m_Objects{};
	const int sceneNr;
	
};
